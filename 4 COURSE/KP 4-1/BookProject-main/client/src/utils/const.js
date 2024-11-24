export const ADMIN_ROUTE = '/admin'
export const LOGIN_ROUTE = '/login'
export const REGISTRATION_ROUTE = '/registration'
export const BOOKS_ROUTE = '/books'
export const BOOK_PAGE_ROUTE = '/bookPage'
export const BOOKMARKS_ROUTE = '/bookmarks'
export const BOOKS_ADMIN_ROUTE = '/booksAdmin'
export const USER_ROUTE = '/user'

export const formatDate = (date) => {
 const moment = require('moment');
  const now = moment();
  const postDate = moment(date);

  // Если разница между датами меньше 1 минуты, выводим "только что"
  if (now.diff(postDate, 'minutes') < 1) {
    return 'только что';
  }

  // Если разница между датами меньше 1 дня, выводим "несколько часов/минут назад"
  if (now.diff(postDate, 'hours') < 24) {
    const diff = now.diff(postDate, 'minutes');
    return `${diff} ${declOfNum(diff, ['минуту', 'минуты', 'минут'])} назад`;
  }

  // Если разница между датами меньше 2 недель, выводим "несколько дней назад"
  if (now.diff(postDate, 'weeks') < 2) {
    const diff = now.diff(postDate, 'days');
    return `${diff} ${declOfNum(diff, ['день', 'дня', 'дней'])} назад`;
  }

  // Во всех остальных случаях выводим полную дату
  return postDate.format('D MMMM YYYY г');
}

// Функция для склонения слов после числительных
const declOfNum = (number, titles) => {
  const cases = [2, 0, 1, 1, 1, 2];
  return titles[(number % 100 > 4 && number % 100 < 20) ? 2 : cases[(number % 10 < 5) ? number % 10 : 5]];
}
