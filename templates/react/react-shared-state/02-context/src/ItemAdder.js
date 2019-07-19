import React from 'react';
import ItemsContext from './ItemsContext';

export default class AddItem extends React.Component {

  constructor(props) {
    super(props);

    this.state = {
      title: '',
    };

    this.submit = this.submit.bind(this);

  }
  static contextType = ItemsContext;

  submit(e) {
    e.preventDefault();

    if (this.state.title.length) {
      this.context.addItem(this.state.title);
      this.setState({ title: '' });
    }
  }

  render() {
    return (
      <form onSubmit={this.submit}>
        <label htmlFor="addItemTitle">Add New Item:</label>
        <input type="text" id="addItemTitle" value={this.state.title} onChange={(e) => { this.setState({ title: e.target.value }) }}></input>
        <button type="submit">Add</button>
      </form>
    )
  }
};
