import { readFile, findStart, navigatePipes } from './utilities/helpers.js';

let pipes = readFile(process.argv[2]);
let start = findStart(pipes);
let length = navigatePipes(pipes, start[0], start[1]);
console.log(length / 2);
