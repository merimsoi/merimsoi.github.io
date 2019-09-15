const todos = (state = [], action) => {
    switch (action.type) {
      case 'FETCH_LIST_SUCCEED':
        console.log('reducer fetch list was called with:',action.list);
        return {
          ...state,                 
          list: action.list,         
        }
      default:
        return state
    }
  }
  
  export default todos
  