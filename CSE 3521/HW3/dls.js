//Perform depth-limited search from initial state, using defined "is_goal_state"
//and "find_successors" functions
//Will not examine paths longer than "depth_limit" (i.e. paths that have "depth_limit" states in them, or "depth_limit-1" actions in them)
//Returns: null if no goal state found
//Returns: object with two members, "actions" and "states", where:
//  actions: Sequence(Array) of action ids required to reach the goal state from the initial state
//  states: Sequence(Array) of states that are moved through, ending with the reached goal state (and EXCLUDING the initial state)
//  The actions and states arrays should both have the same length.
function depth_limited_search(initial_state, depth_limit) {

    let path={
        actions:actions=[],
        states:states=[]
    };
    let state=initial_state;
    if (depth_limit>1) {
        let suc = find_successors(state);
        for (var i=0; i<suc.length; i++) {
            path=depth_limited_search(suc[i].resultState, depth_limit-1);
            if(path==null) {
                path= {
                    actions:actions=[],
                    states:states=[]
                };
            }
            if ((is_goal_state(suc[i].resultState)||path.actions.length>0) && path.states.indexOf(suc[i].resultState)==-1) {
                    path.actions.unshift(suc[i].actionID);
                    path.states.unshift(suc[i].resultState);
                break;
            }
        }
    }
    if (path.actions.length==0) {
        return null;
    }
    else {
        return path;
    }
}
