//author: Patrick Cheng
//report is in report.txt in the zip file folder
//extra credit has been done as well

//Define the order in which to examine/expand possible moves
//(This affects alpha-beta pruning performance)
let move_expand_order = [0, 1, 2, 3, 4, 5, 6, 7, 8]; //Naive (linear) ordering
//let move_expand_order=[4,0,1,2,3,5,6,7,8]; //Better ordering?
//let move_expand_order = [1, 3, 5, 7, 0, 2, 6, 8, 4]; //134903
//let move_expand_order = [4, 0, 8, 1, 2, 5, 3, 6, 7]; //47231
//let move_expand_order = [1, 3, 5, 8, 0, 7, 6, 4, 2]; //120630
//let move_expand_order = [4, 0, 8, 2, 3, 5, 6, 1, 7]; //44016

/////////////////////////////////////////////////////////////////////////////

function tictactoe_minimax(board, cpu_player, cur_player) {
  /***********************************************************
  * board: game state, an array representing a tic-tac-toe board
  * The positions correspond as follows
  * 0|1|2
  * -+-+-
  * 3|4|5 -> [ 0,1,2,3,4,5,6,7,8 ]
  * -+-+-
  * 6|7|8
  * For each board location, use the following:
  *  -1 if this space is blank
  *   0 if it is X
  *   1 if it is O
  *
  * cpu_player: Which piece is the computer designated to play
  * cur_player: Which piece is currently playing
  *   0 if it is X
  *   1 if it is O
  * So, to check if we are currently looking at the computer's
  * moves do: if(cur_player===cpu_player)
  *
  * Returns: Javascript object with 2 members:
  *   score: The best score that can be gotten from the provided game state
  *   move: The move (location on board) to get that score
  ***********************************************************/

  let score_temp = 0, move_temp = 0;
  let new_board;

  //BASE CASE
  if (is_terminal(board)) //Stop if game is over
    return {
      move: null,
      score: utility(board, cpu_player) //How good was this result for us?
    }

  ++helper_expand_state_count; //DO NOT REMOVE
  //GENERATE SUCCESSORS

  if (cur_player == cpu_player) {
    score_temp = -Infinity;
    for (let move of move_expand_order) { //For each possible move (i.e., action)
      if (board[move] != -1) continue; //Already taken, can't move here (i.e., successor not valid)

      new_board = board.slice(0); //Copy
      new_board[move] = cur_player; //Apply move
      //Successor state: new_board

      //RECURSION
      // What will my opponent do if I make this move?
      let results = tictactoe_minimax(new_board, cpu_player, 1 - cur_player);
      if (results.score > score_temp) {
        score_temp = results.score;
        move_temp = move;
      }

    }
  }
  else {
    score_temp = Infinity;
    for (let move of move_expand_order) { //For each possible move (i.e., action)
      if (board[move] != -1) continue; //Already taken, can't move here (i.e., successor not valid)

      new_board = board.slice(0); //Copy
      new_board[move] = cur_player; //Apply move
      //Successor state: new_board

      //RECURSION
      // What will my opponent do if I make this move?
      let results = tictactoe_minimax(new_board, cpu_player, 1 - cur_player);
      if (results.score < score_temp) {
        score_temp = results.score;
        move_temp = move;
      }
    }
  }

  //Return results gathered from all sucessors (moves).
  //Which was the "best" move?  
  return {
    move: move_temp/* What do you return here? */,
    score: score_temp /* And here? */
  };

  //MINIMAX
  /***********************
  * TASK: Implement minimax here. (What do you do with results.move and results.score ?)
  * 
  * Hint: You will need a little code outside the loop as well, but the main work goes here.
  *
  * Hint: Should you find yourself in need of a very large number, try Infinity or -Infinity
  ***********************/

}


function is_terminal(board) {
  ++helper_eval_state_count; //DO NOT REMOVE

  for (var i = 0; i < 3; i++) {
    //check row and columns
    var row = (board[0 + 3 * i] == board[1 + 3 * i] && board[1 + 3 * i] == board[2 + 3 * i] && board[2 + 3 * i] != -1);
    var col = (board[3 * 0 + i] == board[3 * 1 + i] && board[3 * 1 + i] == board[3 * 2 + i] && board[3 * 2 + i] != -1);

    if (row || col) {
      return true;
    }
  }
  //check for diagonal crosses, left_cross is upper left to lower right, right_cross is upper right to lower left
  var left_cross = (board[0] == board[4] && board[4] == board[8] && board[8] != -1);
  var right_cross = (board[2] == board[4] && board[4] == board[6] && board[6] != -1);

  if (left_cross || right_cross || !board.includes(-1)) {
    return true;
  }

  /*************************
  * TASK: Implement the terminal test
  * Return true if the game is finished (i.e, a draw or someone has won)
  * Return false if the game is incomplete
  *************************/
  return false;

}

function utility(board, player) {
  /***********************
  * TASK: Implement the utility function
  *
  * Return the utility score for a given board, with respect to the indicated player
  *
  * Give score of 0 if the board is a draw
  * Give a positive score for wins, negative for losses.
  * Give larger scores for winning quickly or losing slowly
  * For example:
  *   Give a large, positive score if the player had a fast win (i.e., 5 if it only took 5 moves to win)
  *   Give a small, positive score if the player had a slow win (i.e., 1 if it took all 9 moves to win)
  *   Give a small, negative score if the player had a slow loss (i.e., -1 if it took all 9 moves to lose)
  *   Give a large, negative score if the player had a fast loss (i.e., -5 if it only took 5 moves to lose)
  * (DO NOT simply hard code the above 4 values, other scores are possible. Calculate the score based on the above pattern.)
  * (You may return either 0 or null if the game isn't finished, but this function should never be called in that case anyways.)
  *
  * Hint: You can find the number of turns by counting the number of non-blank spaces
  *       (Or the number of turns remaining by counting blank spaces.)
  *   0 if it is X
  *   1 if it is O
  ***********************/

  var tie = true;
  var winner = -1;

  //check for diagonal crosses, left_cross is upper left to lower right, right_cross is upper right to lower left
  var left_cross = (board[0] == board[4] && board[4] == board[8] && board[8] != -1);
  var right_cross = (board[2] == board[4] && board[4] == board[6] && board[6] != -1);

  if (left_cross || right_cross) {
    if (board[4] == 0) {
      winner = 0;
    } else if (board[4] == 1) {
      winner = 1;
    }
    tie = false;
  }

  for (var i = 0; i < 3; i++) {
    //check row and columns
    var row = (board[0 + 3 * i] == board[1 + 3 * i] && board[1 + 3 * i] == board[2 + 3 * i] && board[2 + 3 * i] != -1);
    var col = (board[3 * 0 + i] == board[3 * 1 + i] && board[3 * 1 + i] == board[3 * 2 + i] && board[3 * 2 + i] != -1);

    if (row) {
      if (board[1 + 3 * i] == 0) {
        winner = 0;
      } else if (board[1 + 3 * i] == 1) {
        winner == 1;
      }
      tie = false;
    } else if (col) {
      if (board[3 * 1 + i] == 0) {
        winner = 0;
      } else if (board[3 * 1 + i] == 1) {
        winner = 1;
      }
      tie = false;
    }
  }

  //return scores
  var moves = 9, blank = 0;
  for (var i = 0; i < board.length; ++i) {
    if (board[i] == -1)
      blank++;
  }
  moves = 9 - blank;

  if (winner == player) {
    return 10 - moves;
  } else if (tie) {
    return 0;
  } else {
    return moves - 10;
  }


}

function tictactoe_minimax_alphabeta(board, cpu_player, cur_player, alpha, beta) {
  /***********************
  * TASK: Implement Alpha-Beta Pruning
  *
  * Once you are confident in your minimax implementation, copy it here
  * and add alpha-beta pruning. (What do you do with the new alpha and beta parameters/variables?)
  *
  * Hint: Make sure you update the recursive function call to call this function!
  ***********************/

  let score_temp = 0, move_temp = 0;
  let new_board;

  //BASE CASE
  if (is_terminal(board)) //Stop if game is over
    return {
      move: null,
      score: utility(board, cpu_player) //How good was this result for us?
    }

  ++helper_expand_state_count; //DO NOT REMOVE
  //GENERATE SUCCESSORS

  if (cur_player == cpu_player) {
    score_temp = -Infinity;
    for (let move of move_expand_order) { //For each possible move (i.e., action)
      if (board[move] != -1) continue; //Already taken, can't move here (i.e., successor not valid)

      new_board = board.slice(0); //Copy
      new_board[move] = cur_player; //Apply move
      //Successor state: new_board

      //RECURSION
      // What will my opponent do if I make this move?
      let results = tictactoe_minimax_alphabeta(new_board, cpu_player, 1 - cur_player, alpha, beta);
      if (results.score > score_temp) {
        score_temp = results.score;
        move_temp = move;
      }
      if (alpha < score_temp) {
        alpha = score_temp;
      }
      if (beta < alpha) {
        break;
      }

    }
  }
  else {
    score_temp = Infinity;
    for (let move of move_expand_order) { //For each possible move (i.e., action)
      if (board[move] != -1) continue; //Already taken, can't move here (i.e., successor not valid)

      new_board = board.slice(0); //Copy
      new_board[move] = cur_player; //Apply move
      //Successor state: new_board

      //RECURSION
      // What will my opponent do if I make this move?
      let results = tictactoe_minimax_alphabeta(new_board, cpu_player, 1 - cur_player, alpha, beta);
      if (results.score < score_temp) {
        score_temp = results.score;
        move_temp = move;
      }
      if (beta > score_temp) {
        beta = score_temp;
      }
      if (beta < alpha) {
        break;
      }
    }
  }

  //Return results gathered from all sucessors (moves).
  //Which was the "best" move?  
  return {
    move: move_temp/* What do you return here? */,
    score: score_temp /* And here? */
  };

}

function debug(board, human_player) {
  /***********************
  * This function is run whenever you click the "Run debug function" button.
  *
  * You may use this function to run any code you need for debugging.
  * The current "initial board" and "human player" settings are passed as arguments.
  *
  * (For the purposes of grading, this function will be ignored.)
  ***********************/
  helper_log_write("Testing board:");
  helper_log_board(board);

  let tm = is_terminal(board);
  helper_log_write("is_terminal() returns " + (tm ? "true" : "false"));

  let u = utility(board, human_player);
  helper_log_write("utility() returns " + u + " (w.r.t. human player selection)");
}
