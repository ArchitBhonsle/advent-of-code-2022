const input = await Deno.readTextFile(Deno.args[0]);

interface Cd {
  type: "cd";
  directory: string;
}
interface Ls {
  type: "ls";
  output: Array<{ info: string; name: string }>;
}
type Command = Cd | Ls;

function parseCommand(cmd: string): Command {
  switch (cmd.slice(0, 2)) {
    case "cd":
      return { type: "cd", directory: cmd.slice(3) };
    case "ls":
      return {
        type: "ls",
        output: cmd
          .slice(3)
          .split("\n")
          .map((line) => {
            const [info, name] = line.split(" ").slice(0, 2);
            return { info, name };
          }),
      };
    default:
      throw new Error("unreachable");
  }
}

const commands = input
  .split("$")
  .slice(1)
  .map((line) => line.trim())
  .map(parseCommand);

interface File {
  type: "file";
  name: string;
  size: number;
}
interface Directory {
  type: "directory";
  name: string;
  size?: number;
  contents: Array<Node>;
}
type Node = File | Directory;

function simulateCommands(commands: Array<Command>): Directory {
  const root = { type: "directory", name: "/", contents: [] } as Directory;
  let path: Array<Directory> = [root];

  for (const command of commands) {
    const dir = path.at(-1)!;

    switch (command.type) {
      case "cd": {
        switch (command.directory) {
          case "/": {
            path = path.slice(0, 1);
            break;
          }
          case "..": {
            path.pop();
            break;
          }
          default: {
            let node = dir.contents.find(
              ({ type, name }) =>
                type === "directory" && name === command.directory
            );
            if (!node) {
              node = {
                type: "directory",
                name: command.directory,
                contents: [],
              };
              dir.contents.push(node);
            }

            path.push(node as Directory);
          }
        }
        break;
      }
      case "ls": {
        for (const { info, name } of command.output) {
          if (info === "dir") {
            if (
              !dir.contents.find(
                ({ type, name: fName }) =>
                  type === "directory" && fName === name
              )
            ) {
              dir.contents.push({ type: "directory", name, contents: [] });
            }
          } else {
            const size = parseInt(info);

            if (
              !dir.contents.find(
                ({ type, name: fName }) => type === "file" && fName === name
              )
            ) {
              dir.contents.push({ type: "file", name, size });
            }
          }
        }
        break;
      }
    }
  }

  return root;
}

function getSize(node: Node): number {
  return (
    node.size ||
    (node.size = (node as Directory).contents
      .map(getSize)
      .reduce((a, b) => a + b, 0))
  );
}
const root = simulateCommands(commands);

const totalSize = getSize(root);
const sizeToDelete = 30_000_000 - (70_000_000 - totalSize);
function getCandidate(node: Node): Node | null {
  if (node.type === "file") return null;

  if (getSize(node) < sizeToDelete) return null;

  const childCandidates = node.contents
    .map(getCandidate)
    .filter((fc) => fc !== null) as Array<Node>;

  if (childCandidates.length === 0) return node;

  const minSize = Math.min(...childCandidates.map(getSize));
  return childCandidates.find((c) => getSize(c) === minSize)!;
}

const candidate = getCandidate(root);
if (candidate === null) {
  throw new Error("Could not find a candidate (should be impossible)");
}
console.log(getSize(candidate));
