// Confirming if the values can actually be negative

const input = await Deno.readTextFile("./example2.txt");

const numbers = input
  .split("\n")
  .filter((line) => line.substring(0, 4) === "addx")
  .map((line) => line.substring(5))
  .map((line) => parseInt(line));

const scan = [0];
numbers.forEach((n) => scan.push(scan.at(-1)! + n));

console.log(scan);
