import fs from 'fs'

function readFile(file) {
    let fileContents = fs.readFileSync(file, 'utf-8').trim().split('\n');
    let directions = fileContents.shift().split("");
    // empty line
    fileContents.shift();
    // everything left is the map
    return [directions, fileContents]
};

function parseNodes(nodes) {
    let parsedNodes = new Map();
    while (nodes.length > 0) {
        let node = nodes.shift();

        node = node.split(" = ");
        node[1] = node[1].slice(1, node[1].length - 1).split(", ");

        parsedNodes.set(node[0], node[1]);
    }

    return parsedNodes;
}

function navigateMap(map, node) {
    let steps = 0; 
    while (steps++, node != 'ZZZ') {
        // get & rotate direction
        const direction = map[0].shift();
        map[0].push(direction);

        // navigate
        if (node != 'ZZZ' && direction === 'R') {
            node = map[1].get(node)[1];
        } else {
            node = map[1].get(node)[0];
        }
    }

    return steps;
}

export { readFile, parseNodes, navigateMap };
