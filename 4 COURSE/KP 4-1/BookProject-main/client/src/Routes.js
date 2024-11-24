import { ADMIN_ROUTE } from "./utils/const";
import Auth from "./pages/Auth";
import { BOOKS_ROUTE } from "./utils/const";
import { LOGIN_ROUTE } from "./utils/const";
import { REGISTRATION_ROUTE } from "./utils/const";
import { BOOK_PAGE_ROUTE } from "./utils/const";
import { BOOKS_ADMIN_ROUTE, USER_ROUTE } from "./utils/const";
import BookPage from "./pages/BookPage";
import { BOOKMARKS_ROUTE } from "./utils/const";
import BookMarks from "./components/BookMarks";
import Books from "./pages/Books";
import Admin from "./pages/Admin";
import AdminBook from "./pages/AdminBooks";
import UserPage from "./pages/UserPage";
import BooksFiltr from "./pages/BooksFiltr";
import AuthorPanel from "./components/AuthorPanel";

export const authorRoutes = [
    {
        path: "/author-panel",
        element: AuthorPanel,
    },
];

export const authRoutes = [
    
    {
        path: BOOKMARKS_ROUTE,
        element: BookMarks,

    },
   
    {
        path: USER_ROUTE + '/:id',
        element: UserPage,
    }

];
export const publicRoutes = [
    {
        path: LOGIN_ROUTE,
        element: Auth,
    },
    {
        path: REGISTRATION_ROUTE,
        element: Auth,
    },
    {
        path: BOOKS_ROUTE,
        element: Books,
    },
    {
        path: BOOK_PAGE_ROUTE + '/:id',
        element: BookPage,
    },
    {
        path: '/genre/:sort/:id',
        element: BooksFiltr,
    },
    {
        path: '/tag/:sort/:id',
        element: BooksFiltr,
    },
    {
        path: '/author/:sort/:id',
        element: BooksFiltr,
    },
    {
        path: '/series/:sort',
        element: BooksFiltr,
    },
    {
        path: '/year/:sort',
        element: BooksFiltr,
    },

];

export const adminRoutes = [   
    {
        path: BOOKS_ADMIN_ROUTE,
        element: AdminBook,
    },
    {
        path: ADMIN_ROUTE,
        element: Admin,
    },
]