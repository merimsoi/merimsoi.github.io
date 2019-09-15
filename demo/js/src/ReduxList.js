import React from 'react'

class ReduxList extends React.Component {
    componentDidMount()
    {
        console.log("component did mount in redux list called");
        const {onFetchList} = this.props;
        onFetchList();
    }
    render(){
       const {list} = this.props;
       return (<div>{list}</div>);
    }
}


export default ReduxList;

