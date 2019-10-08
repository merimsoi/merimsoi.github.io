const todos = (state = [], action) => {
  switch (action.type) {
    case 'FETCH_LIST_SUCCEED':
      return {
        ...state,
        list: action.list,
      };
    default:
      return state;
  }
};

export default todos;
