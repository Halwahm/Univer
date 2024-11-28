export const schemaUser = [
  { label: 'ID', field: 'ID' },
  { label: 'Username', field: 'USER_NAME' },
  { label: 'Email', field: 'EMAIL' },
  { label: 'User Info', field: 'USER_INFO' },
  { label: 'Access Level', field: 'ACCESS_LEVEL' },
  { label: 'Date Created', field: 'DATA_CREATE' },
];

export const schemaBook = [
  { label: 'ID', field: 'ID' },
  { label: 'Name', field: 'BOOK_NAME' },
  { label: 'Description', field: 'BOOK_DESCRIPTION' },
  { label: 'Data release', field: 'DATA_RELEASE' },
  { label: 'Book series', field: 'BOOK_SERIES' },
  { label: 'Count Chapters', field: 'CHAPTERS' },
]

export const schemaTag = [
  { label: 'ID', field: 'ID' },
  { label: 'Name', field: 'TAG_NAME' },
]

export const schemaGenre = [
  { label: 'ID', field: 'ID' },
  { label: 'Name', field: 'GENRE_NAME' },
]

export const schemaAuthor = [
  { label: 'ID', field: 'ID' },
  { label: 'Name', field: 'AUTHOR_NAME' },
]

export const schemaFeedback = [
  { label: 'ID', field: 'ID' },
  { label: 'User', field: 'ID_USER' },
  { label: 'Book', field: 'ID_BOOK' },
  { label: 'Rating', field: 'RATING' },
  { label: 'Comment', field: 'FEEDBACK' },
  { label: 'Date', field: 'DATA_CREATE' },
]

