const currentPlayer = document.querySelector(".jogador-atual");

let selected;
let player = "X";

let positions = [
  [1, 2, 3],
  [4, 5, 6],
  [7, 8, 9],
  [1, 4, 7],
  [2, 5, 8],
  [3, 6, 9],
  [1, 5, 9],
  [3, 5, 7],
];

function init() {
  $.ajax({ url: "http://localhost:3000/limpa/dados", method: "GET" });
  selected = [];

  currentPlayer.innerHTML = `JOGADOR DA VEZ: ${player}`;

  document.querySelectorAll(".jogo button").forEach((item) => {
    item.innerHTML = "";
    item.addEventListener("click", newMove);
  });
}

init();

function newMove(e) {
  const index = e.target.getAttribute("data-i");
  e.target.innerHTML = player;
  e.target.removeEventListener("click", newMove);
  selected[index] = player;

  setTimeout(() => {
    check();
  }, [100]);

  player = player === "X" ? "O" : "X";
  currentPlayer.innerHTML = `JOGADOR DA VEZ: ${player}`;
}

function check() {
  let playerLastMove = player === "X" ? "O" : "X";

  const items = selected
    .map((item, i) => [item, i])
    .filter((item) => item[0] === playerLastMove)
    .map((item) => item[1]);

  for (pos of positions) {
    if (pos.every((item) => items.includes(item))) {
      $.ajax({
        url: "http://localhost:3000/resultado", 
        method: "POST", 
        data: { 
          ganhador: playerLastMove 
        }
      })



      alert("O JOGADOR '" + playerLastMove + "' GANHOU!");

      init();
      return;
    }
  }

  if (selected.filter((item) => item).length === 9) {
    alert("DEU EMPATE!");
    playerLastMove = "DEU EMPATE";
    $.ajax({
      url: "http://localhost:3000/resultado", 
      method: "POST", 
      data: { 
        ganhador: playerLastMove 
      }
    })
    init();
    return;
  }

  
}
