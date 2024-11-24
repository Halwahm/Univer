import {$authHost, $host} from "./index";

export const createBook = async (book) => {
    const {data} = await $authHost.post('api/books/', book);
   return data;
}

export const fetchBooks = async (page) => { 
    const {data} = await $host.get('api/books/'+ page)
    return data;
}

export const fetchBookSearch = async (page, searchTerm, filterParams) => {
    try {
        const response = await $host.post(`/api/books/search/${page}`, {
            searchTerm: searchTerm || '',
            filterParams: filterParams || {},
        });
        return response.data;
    } catch (error) {
        console.error("Error in fetchBookSearch:", error.response?.data || error.message);
        throw error;
    }
};

export const fetchBooksByAuthor = async (userId, page) => {
    const { data } = await $authHost.get(`/api/books/author/${userId}/${page}`);
    return data;
};

export const fetchOneBook = async (id) => {
    const {data} = await $host.get('api/books/id/' + id)
    return data;
}

export const editBook = async (id, book) => {
    const { data } = await $authHost.put(`/api/books/${id}`, book);
    return data;
};

export const uploadFile = async (formData) => {
    const {data} = await $authHost.post('api/files/upload', formData)
    return data;
}
export const fetchFile = async (fileName) => {
    const {data} = await $host.get('/' + fileName)
    return data;
}
//Genre fo book
export const getBookIDGenre = async (id) => {
    const {data} = await $host.get('api/genre/book/' + id)//+
    return data;
}
export const delBookIDGenre = async (id, ganre) => {
    const {data} = await $authHost.delete('api/genre/book/' + id + '/' + ganre)//+
    return data;
}
export const addBookIDGenre = async (id, genre) => {
    const {data} = await $authHost.post('api/genre/book/' + id, genre)//+
    return data;
}
//Genre
export const createGenre = async (genre) => {
    const {data} = await $authHost.post('api/genre/', genre)
    return data;
}

export const fetchGanre = async (page) => {
    const {data} = await $host.get('api/genre/'+ page)//+
    return data;
}
export const delGanre = async (id) => {
    const {data} = await $authHost.delete('api/genre/' + id)//+
    return data;
}
//Tag for book
export const getBookIDTag = async (id) => {
    const {data} = await $host.get('api/tag/book/' + id)//+
    return data;
}
export const delBookIDTag = async (id, tag) => {
    const {data} = await $authHost.delete('api/tag/book/' + id + '/' + tag)//+
    return data;
}
export const addBookIDTag = async (id, tag) => {
    const {data} = await $authHost.post('api/tag/book/' + id, tag)//+
    return data;
}

//Tag
export const createTag = async (tag) => {
    const {data} = await $authHost.post('api/tag/', tag)
    return data;
}

export const fetchTags = async (page) => {
    const {data} = await $host.get('api/tag/'+ page)//+
    return data;
}
export const delTag = async (id) => {
    const {data} = await $authHost.delete('api/tag/' + id)//+
    return data;
}
//Author
export const createAuthor = async (author) => {
    const {data} = await $authHost.post('api/author/', author)
    return data;
}
export const fetchAuthor = async (page) => {
    const {data} = await $host.get('api/author/'+ page)
    return data;
}
export const delAuthor = async (id) => {
    const {data} = await $authHost.delete('api/author/' + id)
    return data;
}
export const editAuthor = async (id, author) => {
    const {data} = await $authHost.put('api/author/' + id, author)
    return data;
}
//Author for book
export const addBookAuthor = async (id, author) => {
    const {data} = await $authHost.post('api/author/book/' + id, author)
    return data;
}
export const getBookAuthor = async (id) => {
    const {data} = await $host.get('api/author/book/' + id)
    return data;
}
export const delBookAuthor = async (id, author) => {
    const {data} = await $authHost.delete('api/author/book/' + id + '/' + author)
    return data;
}

//Book fo id
export const deleteBook = async (id) => {
    const {data} = await $authHost.delete('api/books/' + id)
    return data;
}
export const getBookId = async (id) => {
    const {data} = await $host.get('api/books/' + id)
    return data;
}

export const getBookauthor = async (id) => {
    const {data} = await $host.get('api/books/author/' + id)
    return data;
}
export const getBookReadCount = async (id) => {
    const {data} = await $host.get('api/books/read/' + id)
    return data;
}
export const getBookAvarageRaiting = async (id) => {
    const {data} = await $host.get('api/books/raiting/' + id)
    //округлим до 1 знаков после запятой
    data._avg.RATING = Math.round(data._avg.RATING * 10) / 10;
    return data;
}
export const getComments = async (id, page) => {
    const {data} = await $host.get('api/feedback/book/' + id+'/'+ page)
    return data;
}
export const getBookGenre = async (genre) => {
    const {data} = await $host.get('api/books/genre/' + genre)
    return data;
}
