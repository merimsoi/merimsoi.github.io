'use strict';

const REACT_VERSION = React.version;
class LikeButton extends React.Component {
  constructor(props) {
    super(props);
    this.state = { liked: false };
  }

  render() {
    if (this.state.liked) {
      return 'You liked this!';
    }

    return (
      <div>
      <div>React version: {REACT_VERSION}</div>
      <button onClick={() => this.setState({ liked: true }) }>
        Like
      </button>
      </div>
    );
  }
}
let domContainer = document.querySelector('#react-app');
ReactDOM.render(<LikeButton />, domContainer);