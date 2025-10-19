async function fetchState() {
  const res = await fetch('/api/state');
  return await res.json();
}

function renderBoard(boardStr) {
  const boardEl = document.getElementById('board');
  boardEl.innerHTML = '';
  for (let i = 0; i < 9; i++) {
    const cell = document.createElement('div');
    cell.className = 'cell';
    const ch = boardStr[i];
    cell.textContent = ch === '.' ? '' : ch;
    const r = Math.floor(i / 3), c = i % 3;
    cell.addEventListener('click', async () => {
      await fetch('/api/move', {
        method: 'POST',
        headers: { 'Content-Type': 'application/x-www-form-urlencoded' },
        body: `row=${r}&col=${c}`
      });
      await refresh();
    });
    boardEl.appendChild(cell);
  }
}

async function refresh() {
  const state = await fetchState();
  renderBoard(state.board);
  const status = document.getElementById('status');
  if (state.winner) {
    status.textContent = `Winner: ${state.winner}`;
  } else if (state.draw) {
    status.textContent = 'Draw!';
  } else {
    status.textContent = `Current: ${state.current}`;
  }
}

async function main() {
  document.getElementById('reset').addEventListener('click', async () => {
    await fetch('/api/reset', { method: 'POST' });
    await refresh();
  });
  await refresh();
}

main();
