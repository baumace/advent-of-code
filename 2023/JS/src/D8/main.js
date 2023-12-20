import { readFile, parseNodes, navigateMap } from './utilities/helpers.js'

let input = readFile(process.argv[2]);
input.push(parseNodes(input.pop()));

console.log(navigateMap(input, 'AAA') - 1);
