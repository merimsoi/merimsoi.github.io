import { connect } from 'react-redux';
import ReduxList from './ReduxList';

const mapStateToProps = state => {
  return {
    list: state.todos.list,
  };
};

const mapDispatchToProps = dispatch => {
  return {
    onFetchList: id => {
      dispatch({ type: 'FETCH_LIST' });
    },
  };
};

const ReduxComponent = connect(
  mapStateToProps,
  mapDispatchToProps
)(ReduxList);

export default ReduxComponent;
