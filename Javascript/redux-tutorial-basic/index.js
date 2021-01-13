import { createStore } from 'redux';

// const ActionVerb = "Buy Book";

const initialState = {
    countOfBooks : 10
}



const buyBook = () => {
    return {
        type: 'Buy Book',
        info: 'A basic example has been illustrated with redux'
    }
}

const ReducerFn = (state=initialState, action) => {
    switch(action.type) {
        case 'Buy Book' : {
            return {
                ...state,
                countOfBooks: state.countOfBooks-1
            }
        }

        default: {
            return state;
        }
    }
}



const store = createStore(ReducerFn);

console.log('Initial state', store.getState())

const unsubscribeFn = store.subscribe(() => {
    console.log('Updated state', store.getState())
});

store.dispatch(buyBook());
store.dispatch(buyBook());
store.dispatch(buyBook());
store.dispatch(buyBook());

unsubscribeFn();