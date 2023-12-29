import { readFile, populateRow } from './utilities/helpers.js';

let input = readFile(process.argv[2]);
let i = 0;
let sum = 0;
while (i < input.length) {
    let nextRowNum =
        populateRow(input[i]) + parseInt(input[i][input[i].length - 1]);
    sum += nextRowNum;
    i++;
}
