import React from 'react';
import ItemsPage from './ItemsPage';

class App extends React.Component {

  constructor(props) {
    super(props);

    this.state = {
      items: [],
      isLoaded: false,
    };

    this.addItem = this.addItem.bind(this);
  }

  async getDataFromServer() {
    return new Promise(resolve => {
      setTimeout(() => {
        const data = [
          {
            id: 1,
            title: 'First item',
          },
          {
            id: 2,
            title: 'Second item',
          },
        ];
        resolve(data);
      }, 1000);
    });
  }

  async componentDidMount() {
    const items = await this.getDataFromServer();
    this.setState({ items, isLoaded: true });
  }

  addItem(newTitle) {
    const maxId = this.state.items.reduce((maxId, item) => item.id > maxId ? item.id : maxId, 0);
    const newItem = {
      id: maxId + 1,
      title: newTitle,
    }

    const newItems = [ ...this.state.items ];
    newItems.push(newItem);
    this.setState({items: newItems});
  }

  render() {
    if (!this.state.isLoaded) {
      return <p>Loading...</p>
    }

    return (
      <ItemsPage items={this.state.items} addItem={this.addItem} />
    );
  }
}

export default App;
