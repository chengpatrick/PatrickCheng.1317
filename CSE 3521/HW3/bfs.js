//Perform breadth-first search from initial state, using defined "is_goal_state"
//and "find_successors" functions
//Returns: null if no goal state found
//Returns: object with two members, "actions" and "states", where:
//  actions: Sequence(Array) of action ids required to reach the goal state from the initial state
//  states: Sequence(Array) of states that are moved through, ending with the reached goal state (and EXCLUDING the initial state)
//  The actions and states arrays should both have the same length.
function breadth_first_search(initial_state) {
  let open = []; //See push()/pop() and unshift()/shift() to operate like stack or queue
                 //https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Array
  let closed = new Set(); //https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Set

  open.unshift(initial_state);
  var flag = false;
  /***Your code for breadth-first search here***/

    let path=[];
    let actions=[];
    let states=[];
    let state;

  //path.actions.push(null);
  //path.states.push(initial_state);
  //open.push(path);

  while(open.length>0){

  state=open.pop();
  closed.add(state_to_uniqueid(state));
        if (is_goal_state(state)) {
            flag = true;
            break; 
        }
        let suc = find_successors(state);
        for (var i = 0; i < suc.length; i++) {
            if (!(closed.has(state_to_uniqueid(suc[i].resultState)) || open.indexOf(suc[i].resultState) != -1)) {
                open.unshift(suc[i].resultState);
                path.push({
                    actionID: suc[i].actionID,
                    pre: state,
                    resultState: suc[i].resultState
                });
            }
        }
    }
    if (flag == false) {
        return null;
    }

    else {
        let temp = path.find(p => p.resultState == state);
        while (temp.pre != initial_state) {
            actions.unshift(temp.actionID);
            states.unshift(state);
            state = temp.pre;
            temp = path.find(o => o.resultState == state);
        }
        actions.unshift(temp.actionID);
        states.unshift(state); 

        return {
            actions: actions,
            states: states
        };
  
  /*
    let path=open.shift();
     if(!closed.has(state_to_uniqueid(state))) {
      let suc=find_successors(state);
        open.push(newPath);
        if(is_goal_state(suc[i].resultState)){
      }
    }
    closed.add(state_to_uniqueid(state));
  }
  */
  }

  /*
    Hint: In order to generate the solution path, you will need to augment
      the states to store the predecessor/parent state they were generated from
      and the action that generates the child state from the predecessor state.
      
	  For example, make a wrapper object that stores the state, predecessor and action.
	  Javascript objects are easy to make:
		let object={
			member_name1 : value1,
			member_name2 : value2
		};
      
    Hint: Because of the way Javascript Set objects handle Javascript objects, you
      will need to insert (and check for) a representative value instead of the state
      object itself. The state_to_uniqueid function has been provided to help you with
      this. For example
        let state=...;
        closed.add(state_to_uniqueid(state)); //Add state to closed set
        if(closed.has(state_to_uniqueid(state))) { ... } //Check if state is in closed set
  */
  
  /***Your code to generate solution path here***/
  //OR

  //No solution found

  return null;
}

