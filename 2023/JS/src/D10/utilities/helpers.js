import fs from 'fs';
import { get } from 'https';

function readFile(file) {
    let fileContents = fs
        .readFileSync(file, 'utf-8')
        .trim()
        .split('\n')
        .map((entry) => {
            return entry.split('');
        });
    return fileContents;
}

function findStart(pipes) {
    let row = 0;
    let column = 0;
    let found = false;
    while (!found && row < pipes.length) {
        column = 0;
        while (!found && column < pipes[row].length) {
            found = pipes[row][column] === PIPES.START;
            column++;
        }
        row++;
    }
    return [row - 1, column - 1];
}

const DIRECTIONS = Object.freeze({
    LEFT: 3,
    RIGHT: 2,
    UP: 1,
    DOWN: 0,
});

const PIPES = Object.freeze({
    VERTICAL: '|',
    HORIZONTAL: '-',
    NE: 'L',
    NW: 'J',
    SW: '7',
    SE: 'F',
    GROUND: '.',
    START: 'S',
});

function getDirectionsFromPipe(pipe) {
    switch (pipe) {
        case PIPES.VERTICAL:
            return [DIRECTIONS.UP, DIRECTIONS.DOWN];
        case PIPES.HORIZONTAL:
            return [DIRECTIONS.LEFT, DIRECTIONS.RIGHT];
        case PIPES.NE:
            return [DIRECTIONS.UP, DIRECTIONS.RIGHT];
        case PIPES.NW:
            return [DIRECTIONS.UP, DIRECTIONS.LEFT];
        case PIPES.SW:
            return [DIRECTIONS.DOWN, DIRECTIONS.LEFT];
        case PIPES.SE:
            return [DIRECTIONS.DOWN, DIRECTIONS.RIGHT];
        default:
            console.log(`getDirectionsFromPipe error: ${pipe}`);
    }
}

function getOppositeDirection(direction) {
    switch (direction) {
        case DIRECTIONS.DOWN:
            return DIRECTIONS.UP;
        case DIRECTIONS.UP:
            return DIRECTIONS.DOWN;
        case DIRECTIONS.LEFT:
            return DIRECTIONS.RIGHT;
        case DIRECTIONS.RIGHT:
            return DIRECTIONS.LEFT;
    }
}

function handleStartDirection(pipes, row, column) {
    let pipe;
    const pipeDown = row < pipes.length - 1;
    if (pipeDown) {
        pipe = pipes[row + 1][column];
        const canMoveDown =
            pipe === PIPES.VERTICAL || pipe === PIPES.NE || pipe === PIPES.NW;
        if (canMoveDown) {
            return DIRECTIONS.DOWN;
        }
    }
    const pipeUp = row > 0;
    if (pipeUp) {
        pipe = pipes[row - 1][column];
        const canMoveUp =
            pipe === PIPES.VERTICAL || pipe === PIPES.SE || pipe === PIPES.SW;
        if (canMoveUp) {
            return DIRECTIONS.UP;
        }
    }
    const pipeLeft = column > 0;
    if (pipeLeft) {
        pipe = pipes[row][column - 1];
        const canMoveLeft =
            pipe === PIPES.HORIZONTAL || pipe === PIPES.SE || pipe === PIPES.NE;
        if (canMoveLeft) {
            return DIRECTIONS.LEFT;
        }
    }
    const pipeRight = column < pipes[row].length - 1;
    if (pipeRight) {
        pipe = pipes[row][column + 1];
        const canMoveRight =
            pipe === PIPES.HORIZONTAL || pipe === PIPES.NW || pipe === PIPES.SW;
        if (canMoveRight) {
            return DIRECTIONS.RIGHT;
        }
    }
}

function navigatePipes(pipes, row, column) {
    let pipeLength = 0;
    let currentPipe = pipes[row][column];
    let comingFrom;
    do {
        console.log(`${printDirection(comingFrom)} (${row}, ${column})`);
        let nextDirection = null;
        if (currentPipe === PIPES.START) {
            nextDirection = handleStartDirection(pipes, row, column);
        } else {
            let directions = getDirectionsFromPipe(currentPipe);
            nextDirection =
                directions[0] === comingFrom ? directions[1] : directions[0];
        }

        switch (nextDirection) {
            case DIRECTIONS.UP:
                row--;
                break;
            case DIRECTIONS.DOWN:
                row++;
                break;
            case DIRECTIONS.LEFT:
                column--;
                break;
            case DIRECTIONS.RIGHT:
                column++;
                break;
        }

        currentPipe = pipes[row][column];
        pipeLength++;
        comingFrom = getOppositeDirection(nextDirection);
    } while (currentPipe !== PIPES.START);
    return pipeLength;
}

function printDirection(direction) {
    switch (direction) {
        case DIRECTIONS.DOWN:
            return 'Coming from DOWN';
        case DIRECTIONS.UP:
            return 'Coming from UP';
        case DIRECTIONS.LEFT:
            return 'Coming from LEFT';
        case DIRECTIONS.RIGHT:
            return 'Coming from RIGHT';
    }
}

export { readFile, findStart, navigatePipes };
