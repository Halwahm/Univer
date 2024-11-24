import axios from 'axios';

const $host = axios.create({
    baseURL: process.env.REACT_APP_API_URL
});

const $authHost = axios.create({
    baseURL: process.env.REACT_APP_API_URL
});

$authHost.interceptors.request.use(
     
    config => {
        let token = localStorage.getItem('token');
        console.log("Checktoken: ", token);
      config.headers.authorization = `Bearer ${token}`;
      return config;
    },
    error => {
      return Promise.reject(error);
    }
  );


export {
    $host,
    $authHost
}
