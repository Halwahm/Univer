/* eslint-disable jsx-a11y/heading-has-content */
/* eslint-disable jsx-a11y/anchor-is-valid */
import React, {useEffect, useState} from "react";
import {
  AspectRatio,
  Badge,
  Card,
  Center,
  Container,
  Grid,
  Group,
  Image,
  LoadingOverlay,
  Paper,
  Stack,
  Text,
  Title,
  useMantineTheme,
} from "@mantine/core";
import {IconMovie} from "@tabler/icons-react";
import {Carousel} from '@mantine/carousel';
import Store from "../../../store/store";
import {useNavigate} from "react-router-dom";
import {notifications} from "@mantine/notifications";
import {getHumanReadableGenre} from "../../../utils/genreUtils";
import {Buffer} from "buffer";
import Autoplay from "embla-carousel-autoplay";

const AdminGenre = () => {
  const store = new Store();
  const navigate = useNavigate();
  const theme = useMantineTheme();
  const [loading, setLoading] = useState(true);
  const [genres, setGenres] = useState([]);
  const [genreFilms, setGenreFilms] = useState({});

  const fetchGenres = async () => {
    try {
      const response = await store.GetGenreFilm();
      setGenres(response.data);
      
      // Загружаем фильмы для каждого жанра
      const filmsPromises = response.data.map(async (genre) => {
        try {
          const filmsResponse = await store.GetFilmGenre(genre.id);
          return { genreId: genre.id, films: filmsResponse.data };
        } catch (error) {
          console.error(`Error fetching films for genre ${genre.id}:`, error);
          return { genreId: genre.id, films: [] };
        }
      });

      const filmsResults = await Promise.all(filmsPromises);
      const filmsMap = filmsResults.reduce((acc, {genreId, films}) => {
        acc[genreId] = films;
        return acc;
      }, {});

      setGenreFilms(filmsMap);
    } catch (error) {
      notifications.show({
        title: 'Ошибка',
        message: 'Не удалось загрузить список жанров',
        color: 'red',
      });
    } finally {
      setLoading(false);
    }
  };

  useEffect(() => {
    fetchGenres();
  }, []);

  const handleGenreClick = (id, name) => {
    navigate("/FilmGenre", { state: { ID: id, GenreName: name } });
  };

  const handleFilmClick = (filmId) => {
    navigate("/Film", { state: { ID: filmId } });
  };

  if (loading) {
    return (
      <Container size="lg" py="xl">
        <LoadingOverlay visible={true} />
      </Container>
    );
  }

  const getCarouselSlides = (films) => {
    return films.map((film) => (
      <Carousel.Slide key={film.id}>
        <Card
          p={0}
          radius="md"
          style={{ cursor: 'pointer' }}
          onClick={() => handleFilmClick(film.id)}
        >
          <AspectRatio ratio={2/3}>
            <Image
              src={`data:image/jpeg;base64,${Buffer.from(
                film.img.data
              ).toString("base64")}`}
              alt={film.name}
              radius="md"
              fit="cover"
              withPlaceholder
            />
          </AspectRatio>
          <Text size="xs" ta="center" lineClamp={1} p={4}>
            {film.name}
          </Text>
        </Card>
      </Carousel.Slide>
    ));
  };

  return (
    <Container size="lg" py="xl">
      <Stack spacing="xl">
        <Group position="apart">
          <Title order={2}>Жанры</Title>
        </Group>

        <Grid>
          {genres.map((genre) => {
            const autoplay = new Autoplay({ delay: 3000 });
            return (
              <Grid.Col key={genre.id} span={4}>
                <Card
                  shadow="sm"
                  padding="lg"
                  radius="md"
                  withBorder
                >
                  <Card.Section p="md">
                    <Stack spacing="md">
                      <Group position="apart" mb="xs">
                        <Text 
                          weight={500} 
                          size="lg" 
                          style={{ cursor: 'pointer' }}
                          onClick={() => handleGenreClick(genre.id, genre.name)}
                        >
                          {getHumanReadableGenre(genre.name)}
                        </Text>
                        <Badge color="blue" variant="light">
                          <Group spacing={4}>
                            <IconMovie size="1rem" />
                            <Text size="sm">{genreFilms[genre.id]?.length || 0}</Text>
                          </Group>
                        </Badge>
                      </Group>

                      {genreFilms[genre.id]?.length > 0 ? (
                        <Carousel
                          height={280}
                          slideSize="100%"
                          slideGap="sm"
                          align="start"
                          slidesToScroll={1}
                          withControls={false}
                          loop
                          plugins={[autoplay]}
                          onMouseEnter={autoplay.stop}
                          onMouseLeave={autoplay.reset}
                          styles={{
                            viewport: {
                              height: '100%',
                            },
                            container: {
                              height: '100%',
                            },
                          }}
                        >
                          {getCarouselSlides(genreFilms[genre.id])}
                        </Carousel>
                      ) : (
                        <Paper p="sm" radius="md" bg={theme.colors.gray[0]}>
                          <Center>
                            <Text size="sm" color="dimmed">
                              Нет фильмов в этом жанре
                            </Text>
                          </Center>
                        </Paper>
                      )}
                    </Stack>
                  </Card.Section>
                </Card>
              </Grid.Col>
            );
          })}
        </Grid>
      </Stack>
    </Container>
  );
};

export default AdminGenre;
