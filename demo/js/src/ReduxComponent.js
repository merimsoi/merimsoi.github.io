import { connect } from 'react-redux'
import { fetchList } from './actions'
import ReduxList from './ReduxList'

const mapStateToProps = state => {
  return {   
    list: state.todos.list
  }
}

const mapDispatchToProps = dispatch => {
  return {
    onFetchList: id => {     
      dispatch(fetchList("i am list haha!"))
    }
  }
}

const ReduxComponent = connect(
  mapStateToProps,
  mapDispatchToProps
)(ReduxList)

export default ReduxComponent

