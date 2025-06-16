/* eslint-disable jsx-a11y/alt-text */
/* eslint-disable jsx-a11y/heading-has-content */
/* eslint-disable jsx-a11y/anchor-is-valid */
import React, { useEffect, useState } from "react";
import {
  Container,
  Title,
  SimpleGrid,
  Card,
  Image,
  Text,
  Group,
  Badge,
  Stack,
  LoadingOverlay,
  rem,
  useMantineTheme
} from "@mantine/core";
import { IconMovie } from "@tabler/icons-react";
import Store from "../../../store/store";
import { useNavigate } from "react-router-dom";
import { Buffer } from "buffer";
import { notifications } from "@mantine/notifications";

const AdminFavourite = () => {
  const store = new Store();
  const navigate = useNavigate();
  const theme = useMantineTheme();
  const [loading, setLoading] = useState(true);
  const [favorites, setFavorites] = useState([]);

  useEffect(() => {
    const fetchFavorites = async () => {
      try {
        const response = await store.GetFavoriteFilm();
        setFavorites(response.data);
      } catch (error) {
        notifications.show({
          title: 'Ошибка',
          message: 'Не удалось загрузить список любимых фильмов',
          color: 'red',
        });
      } finally {
        setLoading(false);
      }
    };

    fetchFavorites();
  }, []);

  const handleFilmClick = (id) => {
    navigate("/Film", { state: { ID: id } });
  };

  if (loading) {
    return (
      <Container size="lg" py="xl">
        <LoadingOverlay visible={true} />
      </Container>
    );
  }

  return (
    <Container size="lg" py="xl">
      <Stack spacing="xl">
        <Title order={2} align="center" mb="xl">
          Любимые фильмы
        </Title>

        {favorites.length === 0 ? (
          <Card shadow="sm" padding="xl" radius="md" withBorder>
            <Stack align="center" spacing="md">
              <IconMovie size={48} color={theme.colors.gray[6]} />
              <Text size="lg" color="dimmed">
                У вас пока нет любимых фильмов
              </Text>
            </Stack>
          </Card>
        ) : (
          <SimpleGrid
            cols={3}
            spacing="lg"
            breakpoints={[
              { maxWidth: 'md', cols: 2, spacing: 'md' },
              { maxWidth: 'sm', cols: 1, spacing: 'sm' },
            ]}
          >
            {favorites.map((item) => (
              <Card
                key={item.film.id}
                shadow="sm"
                padding="md"
                radius="md"
                withBorder
                onClick={() => handleFilmClick(item.film.id)}
                sx={{
                  cursor: 'pointer',
                  transition: 'transform 0.2s ease',
                  '&:hover': {
                    transform: 'scale(1.02)',
                  },
                }}
              >
                <Card.Section>
                  <Image
                    src={`data:image/jpeg;base64,${Buffer.from(
                      item.film.img.data
                    ).toString("base64")}`}
                    height={300}
                    alt={item.film.name}
                    radius="md"
                  />
                </Card.Section>

                <Group position="apart" mt="md" mb="xs">
                  <Text weight={500} size="lg" lineClamp={1}>
                    {item.film.name}
                  </Text>
                  <Badge color="blue" variant="light">
                    {item.film.year}
                  </Badge>
                </Group>

                <Text size="sm" color="dimmed" lineClamp={2}>
                  {item.film.description}
                </Text>
              </Card>
            ))}
          </SimpleGrid>
        )}
      </Stack>
    </Container>
  );
};

export default AdminFavourite;
