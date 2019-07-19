import { Container } from 'unstated';

class ItemsContainer extends Container {
  constructor() {
    super();
    
    this.state = {
      items: [],
    };
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
}

export default ItemsContainer;