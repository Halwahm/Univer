const rpcWSS = require('rpc-websockets').Server

let server =  new rpcWSS({port: 4000, host:'localhost'});

server.setAuth((l) => {return (l.login === 'admin' && l.password === 'admin') });

function fib(n) {
    var fibonacci = [0, 1]; 

    if (n != 1) {
    for (i = 2; i < n; i++ ) {
        fibonacci[i] = fibonacci[i-1] + fibonacci[i-2];
    }
    return fibonacci;
    }
    else return 0;

}

function factorial(n) {
    return (n > 1) ? n * factorial(n - 1) : 1;
}

server.register('square', (params) => {
    return params.length === 2 ? params[0] * params[1] : Math.pow(params[0],2) * Math.PI;
}).public();

server.register('sum', (params) => {
    let sum = 0;
    params.forEach(item =>{
        if(Number.isInteger(item)) sum += item;
    });

    return sum;
}).public();

server.register('mul', (params) => {
    let mul = 1;
    params.forEach(item => {
        if(Number.isInteger(item)) mul *= item;
    });

    return mul;
}).public();

server.register('fib', (param) => {
    if (param.length === 1 ) {
        console.log(param);
        return fib(param)
    } else {
        return [1];
    }
}).protected();

server.register('fact', (param) => {
    if (param.length === 1) {
        console.log(param);
        return factorial(param)
    }
    else {
        return [1];
    }
}).protected();
