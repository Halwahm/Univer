import {$authHost, $host} from "./index";
import localforage from "localforage";
import jwt_decode from "jwt-decode";

export const registration = async (email, password, role = 'USER') => {
    const {data} = await $host.post('api/users/registration', {email, password, role })
    localStorage.setItem('token', data.token)
    localStorage.setItem('id', data.user.ID)
    localStorage.setItem('role', data.user.ACCESS_LEVEL)
    localStorage.setItem('name', data.user.USER_NAME)
    return jwt_decode(data.token)
}

export const login = async (email, password) => { 
    const {data} = await $host.post('api/users/login', {email, password})
    console.log(data);
    localStorage.setItem('token', data.token)
    localStorage.setItem('id', data.user.ID)
    localStorage.setItem('role', data.user.ACCESS_LEVEL)
    localStorage.setItem('name', data.user.USER_NAME)
    return jwt_decode(data.token)
}

export const check = async () => {
    const {data} = await $authHost.get('api/users/auth')
    localStorage.setItem('token', data.token)
    localStorage.setItem('id', data.user.ID)
    localStorage.setItem('role', data.user.ACCESS_LEVEL)
    localStorage.setItem('name', data.user.USER_NAME)
    return jwt_decode(data.token)
}

export const logout = async () => {
    await localforage.clear();
   
}

export const update = async (id, USER_NAME, USER_INFO) => {
    const {data} = await $authHost.put('api/users/change/' + id, {USER_NAME, USER_INFO})
    return data;
}


export const featchUsers = async (page) => {
    const {data} = await $host.get('api/users/' + page)
    return data;
}

export const getUserInfo = async (id) => {
    const {data} = await $host.get('api/users/id/' + id)
    return data;
}

export const getFeedback = async (id) => {
    const {data} = await $authHost.get('api/users/feedback/' + id)
    return data;
}
export const deleteFeedback = async (id) => {
    const {data} = await $authHost.delete('api/feedback/' + id)
    return data;
}
export const getBookmarks = async (id, sort, page) => {
    console.log(id, sort, page);
    const {data} = await $authHost.get('api/bookmark/user/' + id+ '/' + sort + '/' + page)
    return data;
}

export const getBoomarkId = async (id_user, id_book) => {
    const {data} = await $authHost.get('api/bookmark/user/' + id_user + '/' + id_book)
    return data[0];
}

export const addMarks = async (id_user, id_book, page, marks) => {
    const {data} = await $authHost.post('api/bookmark/', {id_user, id_book, page, marks})
    return data;
}

export const updateMarks = async(id_user, id_book, marks) => {
    const {data} = await $authHost.put('api/bookmark/status/', {id_user, id_book, marks})
    return data;
}
export const deleteUser = async (id) => {
    const {data} = await $authHost.delete('api/users/' + id)
    return data;
}