function buildGrid(which) {
  const rows = parseInt(document.getElementById(which + 'Rows').value);
  const cols = parseInt(document.getElementById(which + 'Cols').value);
  const grid = document.getElementById(which + 'Grid');
  grid.style.gridTemplateColumns = `repeat(${cols}, auto)`;
  grid.innerHTML = '';
  for (let i = 0; i < rows; i++) {
    for (let j = 0; j < cols; j++) {
      const input = document.createElement('input');
      input.type = 'number';
      input.step = 'any';
      input.value = 0;
      input.id = `${which}_${i}_${j}`;
      grid.appendChild(input);
    }
  }
}

function readMatrix(which) {
  const rows = parseInt(document.getElementById(which + 'Rows').value);
  const cols = parseInt(document.getElementById(which + 'Cols').value);
  const m = [];
  for (let i = 0; i < rows; i++) {
    const row = [];
    for (let j = 0; j < cols; j++) {
      const el = document.getElementById(`${which}_${i}_${j}`);
      row.push(parseFloat(el.value) || 0);
    }
    m.push(row);
  }
  return m;
}

function needsMatrixB(op) {
  return op === 'add' || op === 'subtract' || op === 'multiply';
}

function renderResult(result) {
  const out = document.getElementById('output');
  out.classList.remove('error');
  if (Array.isArray(result)) {
    let html = "<table class='matrix-table'>";
    for (const row of result) {
      html += "<tr>" + row.map(v => `<td>${v}</td>`).join('') + "</tr>";
    }
    html += "</table>";
    out.innerHTML = html;
  } else {
    out.innerHTML = `<strong>${result}</strong>`;
  }
}

async function compute() {
  const op = document.getElementById('operation').value;
  const out = document.getElementById('output');
  out.classList.remove('error');
  out.innerHTML = 'Computing...';

  const payload = { a: readMatrix('a') };
  if (needsMatrixB(op)) payload.b = readMatrix('b');

  try {
    const res = await fetch(`/api/${op}`, {
      method: 'POST',
      headers: { 'Content-Type': 'application/json' },
      body: JSON.stringify(payload)
    });
    const data = await res.json();
    if (!res.ok) {
      out.classList.add('error');
      out.innerHTML = `Error: ${data.error}`;
      return;
    }
    renderResult(data.result);
  } catch (err) {
    out.classList.add('error');
    out.innerHTML = `Request failed: ${err.message}`;
  }
}

function toggleBVisibility() {
  const op = document.getElementById('operation').value;
  document.getElementById('bBlock').style.display = needsMatrixB(op) ? 'block' : 'none';
}

document.getElementById('operation').addEventListener('change', toggleBVisibility);
window.onload = () => {
  buildGrid('a');
  buildGrid('b');
  toggleBVisibility();
};
