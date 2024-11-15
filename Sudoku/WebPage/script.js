const N = 9;
let a = Array.from(Array(N), () => Array(N).fill(0));
let r = Array.from(Array(N), () => Array(N + 1).fill(0));
let c = Array.from(Array(N), () => Array(N + 1).fill(0));
let b = Array.from(Array(N), () => Array(N + 1).fill(0));

document.addEventListener("DOMContentLoaded", initializeGrid);

function BoxNumber(x, y) {
    return Math.floor(x / 3) * 3 + Math.floor(y / 3);
}

function initializeGrid() {
    const grid = document.getElementById("sudokuGrid").querySelector("tbody");
    for (let i = 0; i < N; i++) {
        const row = document.createElement("tr");
        for (let j = 0; j < N; j++) {
            const cell = document.createElement("td");
            const input = document.createElement("input");
            input.type = "text";
            input.maxLength = "1";
            input.oninput = () => validateInput(input, i, j);
            cell.appendChild(input);
            row.appendChild(cell);
        }
        grid.appendChild(row);
    }
}

function validateInput(input, x, y) {
    const value = input.value;
    const message = document.getElementById("message");
    if (value === "" || (value >= "1" && value <= "9")) {
        message.textContent = "";
        a[x][y] = value === "" ? 0 : parseInt(value);
        input.setAttribute("data-user", value ? "true" : "false"); // Track user input
    } else {
        message.textContent = "Invalid input! Please enter numbers 1-9 only.";
        input.value = "";
    }
}

function initializeSolver() {
    for (let i = 0; i < N; i++) {
        for (let j = 0; j < N; j++) {
            if (a[i][j]) {
                const num = a[i][j];
                if (r[i][num] || c[j][num] || b[BoxNumber(i, j)][num]) {
                    document.getElementById("message").textContent = `Error: ${num} is repeated!`;
                    return false;
                }
                r[i][num] = 1;
                c[j][num] = 1;
                b[BoxNumber(i, j)][num] = 1;
            }
        }
    }
    return true;
}

function call(id) {
    if (id === N * N) return true;
    const x = Math.floor(id / N);
    const y = id % N;
    if (a[x][y]) return call(id + 1);

    for (let i = 1; i <= N; i++) {
        if (!r[x][i] && !c[y][i] && !b[BoxNumber(x, y)][i]) {
            r[x][i] = c[y][i] = b[BoxNumber(x, y)][i] = 1;
            a[x][y] = i;

            if (call(id + 1)) return true;

            r[x][i] = c[y][i] = b[BoxNumber(x, y)][i] = a[x][y] = 0;
        }
    }
    return false;
}

function solveSudoku() {
    // Reset row, column, and box checks
    r = Array.from(Array(N), () => Array(N + 1).fill(0));
    c = Array.from(Array(N), () => Array(N + 1).fill(0));
    b = Array.from(Array(N), () => Array(N + 1).fill(0));

    // Initialize solver with current grid values
    if (!initializeSolver()) return;

    if (!call(0)) {
        document.getElementById("message").textContent = "No solution found!";
        return;
    }
    document.getElementById("message").textContent = "Solution found!";
    updateGrid();
}

function updateGrid() {
    const grid = document.getElementById("sudokuGrid").querySelectorAll("input");
    let index = 0;
    for (let i = 0; i < N; i++) {
        for (let j = 0; j < N; j++) {
            const cell = grid[index++];
            cell.classList.remove("user-input", "generated-value"); // Reset classes
            cell.value = a[i][j] || "";
            if (a[i][j] !== 0) {
                if (cell.getAttribute("data-user") === "true") {
                    cell.classList.add("user-input");
                } else {
                    cell.classList.add("generated-value");
                }
            }
        }
    }
}

function resetGrid() {
    a = Array.from(Array(N), () => Array(N).fill(0));
    r = Array.from(Array(N), () => Array(N + 1).fill(0));
    c = Array.from(Array(N), () => Array(N + 1).fill(0));
    b = Array.from(Array(N), () => Array(N + 1).fill(0));
    document.getElementById("message").textContent = "";
    document.querySelectorAll("input").forEach(cell => {
        cell.value = "";
        cell.removeAttribute("data-user"); // Remove user tracking
        cell.classList.remove("user-input", "generated-value");
    });
}
