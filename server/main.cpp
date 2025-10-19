#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#include <cstring>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "tictactoe.h"

static const int PORT = 8080;

struct HttpRequest {
    std::string method;
    std::string path;
    std::string body;
};

std::string httpResponse(int status, const std::string &statusText, const std::string &contentType, const std::string &body) {
    std::ostringstream oss;
    oss << "HTTP/1.1 " << status << " " << statusText << "\r\n";
    oss << "Content-Type: " << contentType << "\r\n";
    oss << "Content-Length: " << body.size() << "\r\n";
    oss << "Connection: close\r\n\r\n";
    oss << body;
    return oss.str();
}

std::string loadFile(const std::string &path) {
    FILE *f = fopen(path.c_str(), "rb");
    if (!f) return "";
    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    fseek(f, 0, SEEK_SET);
    std::string data;
    data.resize(size);
    fread(data.data(), 1, size, f);
    fclose(f);
    return data;
}

HttpRequest parseRequest(const std::string &raw) {
    HttpRequest req;
    std::istringstream iss(raw);
    iss >> req.method >> req.path;
    auto pos = raw.find("\r\n\r\n");
    if (pos != std::string::npos) {
        req.body = raw.substr(pos + 4);
    }
    return req;
}

std::string urlDecode(const std::string &s) {
    std::string out;
    out.reserve(s.size());
    for (size_t i = 0; i < s.size(); ++i) {
        if (s[i] == '+') out.push_back(' ');
        else if (s[i] == '%' && i + 2 < s.size()) {
            std::string hex = s.substr(i + 1, 2);
            char ch = static_cast<char>(strtol(hex.c_str(), nullptr, 16));
            out.push_back(ch);
            i += 2;
        } else out.push_back(s[i]);
    }
    return out;
}

std::vector<std::pair<std::string,std::string>> parseQuery(const std::string &q) {
    std::vector<std::pair<std::string,std::string>> kvs;
    size_t start = 0;
    while (start < q.size()) {
        size_t amp = q.find('&', start);
        if (amp == std::string::npos) amp = q.size();
        size_t eq = q.find('=', start);
        if (eq != std::string::npos && eq < amp) {
            std::string key = urlDecode(q.substr(start, eq - start));
            std::string val = urlDecode(q.substr(eq + 1, amp - (eq + 1)));
            kvs.push_back({key, val});
        }
        start = amp + 1;
    }
    return kvs;
}

int main() {
    TicTacToe game;

    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        perror("socket");
        return 1;
    }

    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(PORT);

    if (bind(server_fd, (sockaddr *)&addr, sizeof(addr)) < 0) {
        perror("bind");
        close(server_fd);
        return 1;
    }

    if (listen(server_fd, 10) < 0) {
        perror("listen");
        close(server_fd);
        return 1;
    }

    std::cout << "Server running on http://localhost:" << PORT << std::endl;

    while (true) {
        int client_fd = accept(server_fd, nullptr, nullptr);
        if (client_fd < 0) {
            perror("accept");
            continue;
        }

        char buffer[8192];
        ssize_t n = recv(client_fd, buffer, sizeof(buffer) - 1, 0);
        if (n <= 0) { close(client_fd); continue; }
        buffer[n] = '\0';
        std::string raw(buffer);
        HttpRequest req = parseRequest(raw);

        std::string response;
        if (req.method == "GET" && (req.path == "/" || req.path == "/index.html")) {
            std::string body = loadFile("/workspace/public/index.html");
            if (body.empty()) body = "<h1>Not Found</h1>";
            response = httpResponse(200, "OK", "text/html; charset=utf-8", body);
        } else if (req.method == "GET" && req.path.rfind("/api/state", 0) == 0) {
            std::ostringstream body;
            body << "{\"board\":\"" << game.toString() << "\",";
            body << "\"current\":\"" << (game.getCurrentPlayer() == TicTacToe::Player::X ? "X" : "O") << "\",";
            body << "\"winner\":\"" << (game.getWinner() == TicTacToe::Player::None ? "" : (game.getWinner() == TicTacToe::Player::X ? "X" : "O")) << "\",";
            body << "\"draw\":" << (game.isDraw() ? "true" : "false") << "}";
            response = httpResponse(200, "OK", "application/json", body.str());
        } else if (req.method == "POST" && req.path.rfind("/api/move", 0) == 0) {
            // Expect body like row=0&col=1
            int row = -1, col = -1;
            auto posQ = req.body.find_first_not_of("\r\n");
            std::string form = posQ == std::string::npos ? req.body : req.body.substr(posQ);
            auto kvs = parseQuery(form);
            for (auto &kv : kvs) {
                if (kv.first == "row") row = std::stoi(kv.second);
                if (kv.first == "col") col = std::stoi(kv.second);
            }
            bool ok = game.makeMove(row, col);
            std::ostringstream body;
            body << "{\"ok\":" << (ok ? "true" : "false") << "}";
            response = httpResponse(ok ? 200 : 400, ok ? "OK" : "Bad Request", "application/json", body.str());
        } else if (req.method == "POST" && req.path == "/api/reset") {
            game.reset();
            response = httpResponse(200, "OK", "application/json", "{\"ok\":true}");
        } else if (req.method == "GET" && req.path.rfind("/public/", 0) == 0) {
            std::string filePath = "/workspace" + req.path;
            std::string body = loadFile(filePath);
            std::string contentType = req.path.find(".css") != std::string::npos ? "text/css" : "application/octet-stream";
            if (req.path.find(".js") != std::string::npos) contentType = "text/javascript";
            response = httpResponse(body.empty() ? 404 : 200, body.empty() ? "Not Found" : "OK", contentType, body.empty() ? std::string("Not Found") : body);
        } else {
            response = httpResponse(404, "Not Found", "text/plain", "Not Found");
        }

        send(client_fd, response.c_str(), response.size(), 0);
        close(client_fd);
    }

    close(server_fd);
    return 0;
}
