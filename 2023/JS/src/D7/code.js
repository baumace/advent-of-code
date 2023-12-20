import fs from 'fs'
import { TYPE_ENUMS, CARD_ENUMS } from './card_constants.js'

function splitElements(element) {
    return element.split(" ");
}

function countCards(hand) {
    let handCounts = {
        'A': 0,
        'K': 0,
        'Q': 0,
        'J': 0,
        'T': 0,
        '9': 0,
        '8': 0,
        '7': 0,
        '6': 0,
        '5': 0,
        '4': 0,
        '3': 0,
        '2': 0,
    };

    hand = hand.split("");
    hand.forEach((card) => {
        handCounts[card] += 1;
    });

    return handCounts;
}

function determineHandType(hand) {
    let counts = countCards(hand);

    let fiveFlag = 0;
    let fourFlag = 0;
    let threeFlag = 0;
    let twoFlag = 0;
    Object.keys(counts).forEach((key) => {
        const count = counts[key];
        // auto returns
        if (count === 5) {
            fiveFlag++;
        } 
        if (count === 4) {
            fourFlag++;
        }
        // multiple counts
        if (count === 3) {
            threeFlag++;
        } else if (count === 2) {
            twoFlag++;
        }
    });

    const fiveOfKind = fiveFlag > 0;
    const fourOfKind = fourFlag > 0;
    const threeOfKind = threeFlag > 0;
    const twoPairs = twoFlag > 1;
    const onePair = twoFlag === 1;
    const fullHouse = threeOfKind && onePair;

    if (fiveOfKind) return TYPE_ENUMS.FIVE_KIND;
    if (fourOfKind) return TYPE_ENUMS.FOUR_KIND;
    if (fullHouse) return TYPE_ENUMS.FULL_HOUSE;
    if (threeOfKind) return TYPE_ENUMS.THREE_KIND;
    if (twoPairs) return TYPE_ENUMS.TWO_PAIR;
    if (onePair) return TYPE_ENUMS.ONE_PAIR;
    return TYPE_ENUMS.HIGH_CARD;
}

function convertToEnum(card) {
    switch (card) {
        case 'A':
            return CARD_ENUMS.ACE;
        case 'K':
            return CARD_ENUMS.KING;
        case 'Q':
            return CARD_ENUMS.QUEEN;
        case 'J':
            return CARD_ENUMS.JACK;
        case 'T':
            return CARD_ENUMS.TEN;
        case '9':
            return CARD_ENUMS.NINE;
        case '8':
            return CARD_ENUMS.EIGHT;
        case '7':
            return CARD_ENUMS.SEVEN;
        case '6':
            return CARD_ENUMS.SIX;
        case '5':
            return CARD_ENUMS.FIVE;
        case '4':
            return CARD_ENUMS.FOUR;
        case '3':
            return CARD_ENUMS.THREE;
        case '2':
            return CARD_ENUMS.TWO;
    }
    return -1;
}

function compareCards(card1, card2) {
    if (card1 === card2) {
        return 0;
    } else {
        return convertToEnum(card1) - convertToEnum(card2);
    }
}

function rankHands(hand1, hand2) {
    if (hand1[2] !== hand2[2]) {
        return hand1[2] - hand2[2];
    } else {
        let i = 0;
        let comparison;
        do {
            comparison = compareCards(hand1[0][i], hand2[0][i]);
            i++;
        } while (comparison === 0);
        return comparison;
    }
}

let filePath = process.argv[2];
let input = fs.readFileSync(filePath, 'utf-8').trim().split('\n').map(splitElements);
input.forEach((line) => {
    line.push(determineHandType(line[0]));
});
input.sort(rankHands);
let total = 0;
for (let i = 1; i <= input.length; i++) {
    total += input[input.length - i][1]*i;
}
console.log(total);
