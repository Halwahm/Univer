export const genreNameMap = {
  'action': 'Боевик',
  'adventure': 'Приключения',
  'animation': 'Мультфильм',
  'comedy': 'Комедия',
  'crime': 'Криминал',
  'documentary': 'Документальный',
  'drama': 'Драма',
  'family': 'Семейный',
  'fantasy': 'Фэнтези',
  'history': 'История',
  'horror': 'Ужасы',
  'music': 'Музыка',
  'mystery': 'Детектив',
  'romance': 'Мелодрама',
  'scifi': 'Научная фантастика',
  'tvmovie': 'Телефильм',
  'thriller': 'Триллер',
  'war': 'Военный',
  'western': 'Вестерн'
};

export const getHumanReadableGenre = (genreName) => {
  return genreNameMap[genreName] || genreName;
};