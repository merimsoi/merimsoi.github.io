import React from 'react';
import { Subscribe } from 'unstated';
import ItemsPage from './ItemsPage';
import ItemsContainer from './ItemsContainer';

class App extends React.Component {

  constructor(props) {
    super(props);

    this.state = {
      isLoaded: false,
    };
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
    this.props.container.setState({ items });
    this.setState({ isLoaded: true });
  }

  render() {
    if (!this.state.isLoaded) {
      return <p>Loading...</p>
    }

    return (
      <ItemsPage />
    );
  }
}

export default () => (
  <Subscribe to={[ItemsContainer]}>
    {container => (
      <App container={container} />
    )}
  </Subscribe>
);
