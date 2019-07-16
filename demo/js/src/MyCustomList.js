import React from 'react';
import request from './requests';

export default async function MyCustomList() {
    const items= await request();
    console.log(items + ' from render');
    return (
        <div>{items}</div>
    );
}