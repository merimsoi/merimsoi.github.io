// https://github.com/facebook/react/issues/15201
// https://reactjs.org/blog/2018/11/27/react-16-roadmap.html#react-16x-mid-2019-the-one-with-suspense-for-data-fetching
import React, { Suspense } from 'react';
import Loader from './Loader';
import ErrorBoundary from './ErrorBoundary';
// import asyncComponent from './components/AsyncComponent';

const Artists = React.lazy(() => import('./components/Artists'));
// const MyStateList = React.lazy(() => import('./components/MyStateList'));
// const ReduxComponent = React.lazy(() => import('./components/ReduxComponent'));
// const CacheComponent = React.lazy(() => import('./components/CacheComponent'));
// const FailingComponent = React.lazy(() => import('./components/MyFailList'));
// const MyAsyncStateList = asyncComponent(() => import('./components/MyStateList'));
import FancyButton from './FancyButton';

export default function MainContainer() {
  const ref = React.createRef();
  const handleClick = () =>
    ref.current.scrollIntoView({
      behavior: 'smooth',
      block: 'start',
    });
  return (
    <div>
      <button type="button" onClick={handleClick}>
        Scroll
      </button>
      <ErrorBoundary>
        <Suspense fallback={<Loader />}>
          <Artists />
        </Suspense>
      </ErrorBoundary>
      <FancyButton ref={ref}>Click me!</FancyButton>
      {/* <ErrorBoundary>
        <Suspense fallback={<Loader />}>
          <MyStateList />
        </Suspense>
      </ErrorBoundary> */}
      {/* <ErrorBoundary>
        <Suspense fallback={<Loader />}>
          <ReduxComponent />
        </Suspense>
      </ErrorBoundary> */}
      {/* <ErrorBoundary>
        <Suspense fallback={<Loader />}>
          <CacheComponent />
        </Suspense>
      </ErrorBoundary> */}
      {/* <ErrorBoundary>
        <Suspense fallback={<Loader />}>
          <FailingComponent />
        </Suspense>
      </ErrorBoundary> */}
      {/* <ErrorBoundary>
        <Suspense fallback={<Loader />}>
          <MyAsyncStateList />
        </Suspense>
      </ErrorBoundary> */}
    </div>
  );
}
