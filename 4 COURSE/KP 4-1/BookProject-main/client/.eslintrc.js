module.exports = {
  parserOptions: {
    ecmaVersion: 2021,
    sourceType: 'module',
    ecmaFeatures: {
      jsx: true
    }
  },
  env: {
    browser: true,
    es2021: true
  },
  plugins: [
    'react',
    'react-hooks',
    'jsx-a11y'
  ],
  extends: [
    'eslint:recommended',
    'plugin:react/recommended',
    'plugin:jsx-a11y/recommended'
  ],
  rules: {
    'no-unused-vars': 'off',
    'react/prop-types': 'off',
    'react-hooks/exhaustive-deps': 'off'
  },
  settings: {
    react: {
      version: 'detect'
    }
  }
};
