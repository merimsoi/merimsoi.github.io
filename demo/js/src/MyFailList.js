import React from 'react';
import fetch from 'isomorphic-fetch';

async function request(){
    return await fetch('http://localhost:5000/api/getFailedResponse');   
}

class MyFailList extends React.Component{
    constructor(props){
        super(props);
        this.state = {
            component: null
        }
    }
    async componentDidMount()
    {
        console.log('component did mount called');
        const result = await request();
        console.log(result);
        const myListResponse = result.json;   
        this.setState({component: myListResponse});              
    }
    render()
    {     
        const {component} = this.state; 
        if (component !== null)
        {             
            return <div>{component}</div>;    
        }
        else
        {
            return <></>;
        }
       
    }
}

export default MyFailList;