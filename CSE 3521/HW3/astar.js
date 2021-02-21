//Perform breadth-first search from initial state, using defined "is_goal_state"
//and "find_successors" functions
//Returns: null if no goal state found
//Returns: object with two members, "actions" and "states", where:
//  actions: Sequence(Array) of action ids required to reach the goal state from the initial state
//  states: Sequence(Array) of states that are moved through, ending with the reached goal state (and EXCLUDING the initial state)
//  The actions and states arrays should both have the same length.

function astar_search(initial_state) {
  let open = new FastPriorityQueue(function (a, b) { return a.estimated_total_cost < b.estimated_total_cost; });
  let closed = new Set();
  let fixed_step_cost =1; //Assume action cost is constant
  var flag=false;
  /***Your code for A* search here***/

  /*
    Hint: A* is very similar to BFS, you should only need to make a few small modifications to your BFS code.
	
    You will need to add values to your augmented state for path cost and estimated total cost.
    I suggest you use the member name "estimated_total_cost" so that the above priority queue code will work.
    
    Call function calculate_heuristic(state) (provided for you) to calculate the heuristic value for you.
	
    See (included) FastPriorityQueue.js for priority queue usage example.
  */

  let path={
    state:[],
    predecessor:[],
    action:[],
    cost:0,
    estimated_total_cost:0
  };

  open.add({
    state: initial_state,
    predecessor:[],
    action:[],
    cost:0,
    estimated_total_cost: calculate_heuristic(initial_state)
    });

  while (!flag && open.length!= 0){
    path=open.poll();
    if (!closed.has(state_to_uniqueid(path.state))){
      if (is_goal_state(path.state)){
        flag=true;
      }
      else{
        let suc=find_successors(path.state);
        while (suc.length!=0){
          let temp=suc.shift();
          let pre=path.predecessor.map(x => x);
          pre.push(path.state);
          let action_path=path.action.map(x => x);
          action_path.push(temp.actionID);
          let path_cost=path.cost + fixed_step_cost;

          open.add({
            state:temp.resultState,
            predecessor:pre,
            action:action_path,
            cost:path_cost,
            estimated_total_cost:path_cost + calculate_heuristic(temp.resultState) 
          })
        }
        closed.add(state_to_uniqueid(path.state));
      }
    }
  }

  if (flag) {
    path.predecessor.push(path.state);
    path.predecessor.shift();
    return {
      actions:path.action /*array of action ids*/,
      states:path.predecessor /*array of states*/
    };
  }

  //OR

  //No solution found
  return null;
}