import React, { useEffect, useState } from 'react';
import { Container } from '@mantine/core';
import { DataFilm } from './DataFilm';
import store from '../../store';

const Film = () => {
  const [data, setData] = useState([]);
  const [dataName, setDataName] = useState('');
  const [dataImage, setDataImage] = useState('');
  const [favorite, setFavorite] = useState(false);

  const fetchFavorite = async () => {
    try {
      const response = await store.getFavorite();
      setFavorite(response.data);
    } catch (error) {
      console.error("Ошибка при получении избранных фильмов:", error);
    }
  };

  const handleFavoriteChange = async () => {
    await fetchFavorite();
  };

  useEffect(() => {
    fetchFavorite();
  }, []);

  return (
    <Container size="xl" py="xl">
      <DataFilm
        data={data}
        dataName={dataName}
        dataImage={dataImage}
        dataFavorite={favorite}
        onFavoriteChange={handleFavoriteChange}
      />
    </Container>
  );
};

export default Film; 