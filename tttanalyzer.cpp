// Copyright 2021 Landon Kushimi lsk1801@bu.edu
// Copyright 2021 Brian Homoon Jung brianhmj@bu.edu
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include "movedef.h"

using std::cout;
using std::string;
using std::vector;

string convertbase(int num) {
  if (num == 0) {
    return "0";
  }
  std::string result = "";
  int digit;
  int index = 0;
  while (num > 0) {
    digit = num % 3;
    num /= 3;
    result = std::to_string(digit) + result;
  }
  return result;
}

bool findSequence(string index, string winningSequence) {
  for (int i = 0; i < winningSequence.length(); i++) {
    if (index.find(winningSequence.at(i)) == string::npos) {
      return false;
    } else {
      continue;
    }
  }
  return true;
}

char tttresult(string  board) {
  if (board.length() != 9) {
    return 'e';
  }

  int xcount = 0;
  int ocount = 0;
  std::string xIndex, oIndex;

  for (int i = 0; i < board.length(); i++) {
    if (board.at(i) != '#' && board.at(i) != 'x' && board.at(i) != 'o') {
      return 'e';
    }
    if (board.at(i) == 'o') {
      ocount++;
      oIndex.push_back('0' + i);
    }
    if (board.at(i) == 'x') {
      xcount++;
      xIndex.push_back('0' + i);
    }
  }

  if (ocount > xcount || xcount > ocount + 1) {
    return 'i';
  }

  vector<string> winningPositions =
  {"012", "345", "678", "036", "147", "258", "048", "246"};

  bool xWin = false, oWin = false;

  for (int i = 0; i < winningPositions.size(); i++) {
    if (findSequence(xIndex, winningPositions.at(i)) == true) {
      xWin = true;
    }
    if (findSequence(oIndex, winningPositions.at(i)) == true) {
      oWin = true;
    }
  }

  if (xWin && oWin) {
    return 'i';
  }

  if (oWin && ocount < xcount) {
    return 'i';
  } else if (oWin) {
    return 'o';
  }

  if (xWin && xcount <= ocount) {
    return 'i';
  } else if (xWin) {
    return 'x';
  }

  if (board.find('#') == string::npos) {
    return 't';
  }

  return 'c';
}

char tttresult(vector<Move> board) {
  std::string xIndex, oIndex;
  string emptyBoard = "#########";

  if (board.at(0).player == 'o') {
    return 'i';
  } else if (board.at(0).player != 'x') {
    return 'e';
  }

  char previousPlayer = ' ';

  for (int i = 0; i < board.size(); i++) {
    if (board.at(i).player == 'x' && board.at(i).r < 3 && board.at(i).c < 3) {
      if (previousPlayer == 'x') {
        return 'i';
      }
      emptyBoard.at((board.at(i).r * 3) + board.at(i).c) = 'x';
      previousPlayer = 'x';
    } else if (board.at(i).player == 'o'
               && board.at(i).r < 3
               && board.at(i).c < 3) {
      if (previousPlayer == 'o') {
        return 'i';
      }
      emptyBoard.at((board.at(i).r * 3) + board.at(i).c) = 'o';
      previousPlayer = 'o';
    } else {
      return 'e';
    }
  }
  return tttresult(emptyBoard);
}

vector<string> get_all_boards() {
  vector<string> boards;
  string emptyString = "#########";
  string baseThree;
  int lengthThree;
  for (int i = 0; i < 19683; i++) {
    baseThree = convertbase(i);
    lengthThree = baseThree.length() - 1;
    for (int j = lengthThree, k = 8; j >= 0 && k >= 0; j--, k--) {
      // std::cout<<"j is currently "<<j<<std::endl;
      if (baseThree.at(j) == '1') {
        emptyString.at(k) = 'o';
      } else if (baseThree.at(j) == '2') {
        emptyString.at(k) = 'x';
      } else if (baseThree.at(j) == '0') {
        emptyString.at(k) = '#';
      }
    }
    boards.push_back(emptyString);
  }
  return boards;
}

void ttt_tally() {
  string keys = "xotic";
  std::map <char, int> tally =
  {{'x', 0}, {'o', 0}, {'t', 0}, {'i', 0}, {'c', 0}};
  char result;

  vector<string> boards = get_all_boards();

  for (int i = 0; i < boards.size(); i++) {
    result = tttresult(boards.at(i));
    tally.at(result) += 1;
  }

  for (int j = 0; j < keys.size(); j++) {
    std::cout << keys.at(j) << " " << tally.at(keys.at(j)) << std::endl;
  }
}

// This version of main interactively
// tests either:
//
//  string tttresult "s"
//  vector tttresult "v"
// or
//  get_all_boards "a"
//
//  also tests
//   ttt_tally  "t"


// MAIN
// note: std:: is included
// everywhere here because
// it is not required to do the using std::
// statements in the preamble

int main() {
  int n;
  std::string board;
  Move m;
  std::vector<Move> moves;
  std::vector<std::string> boards;
  std::string asktype;

  while (std::cin >> asktype) {
    if (asktype == "v") {  // test tttresult vector
      moves.clear();
      std::cin >> n;
      for (int i = 0; i < n; i++) {
        std::cin >> m.r >> m.c >> m.player;
        moves.push_back(m);
      }
      std::cout << tttresult(moves) << "\n";
    } else if (asktype == "s") {  // test tttresult string
      std::cin >> board;
      std::cout << tttresult(board) << "\n";
    } else if (asktype == "a") {  // test get_all_boards
      boards = get_all_boards();
      for (auto b : boards) {
        std::cout << b << "\n";
      }
    } else if (asktype == "t") {  // test ttt_tally
      ttt_tally();
    } else {
      return 0;
    }
  }
  return 0;
}
