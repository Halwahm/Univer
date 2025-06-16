/* eslint-disable jsx-a11y/alt-text */
/* eslint-disable jsx-a11y/heading-has-content */
/* eslint-disable jsx-a11y/anchor-is-valid */
import {useEffect, useState} from "react";
import {useLocation, useNavigate} from "react-router-dom";
import Store from "../../../store/store";
import {
  AspectRatio,
  Badge,
  Card,
  Center,
  Container,
  Divider,
  Group,
  Image,
  Loader,
  Paper,
  Stack,
  Text,
  Title,
  useMantineTheme,
} from "@mantine/core";
import {getHumanReadableGenre} from "../../../utils/genreUtils";
import {IconCalendar, IconClock, IconMovie} from "@tabler/icons-react";
import {Buffer} from "buffer";

const GenreFilm = () => {
  const [dataFilms, setDataFilms] = useState([]);
  const [loading, setLoading] = useState(true);
  const store = new Store();
  const navigate = useNavigate();
  const location = useLocation();
  const theme = useMantineTheme();
  
  const idGenre = location.state?.ID;
  const genreName = location.state?.GenreName;

  useEffect(() => {
    const fetchData = async () => {
      try {
        setLoading(true);
        const res = await store.GetFilmGenre(idGenre);
        setDataFilms(res.data);
      } catch (error) {
        console.error("Error fetching films:", error);
      } finally {
        setTimeout(() => setLoading(false), 300);
      }
    };
    
    if (idGenre) {
      fetchData();
    }
  }, [idGenre]);

  const handleClick = (id) => {
    navigate("/Film", { state: { ID: id } });
  };

  const formatDuration = (duration) => {
    if (!duration) return "Не указано";
    const [hours, minutes] = duration.split(':');
    return `${hours} ч ${minutes} мин`;
  };

  const formatDate = (dateString) => {
    if (!dateString) return "Не указано";
    const date = new Date(dateString);
    return date.toLocaleDateString("ru-RU", {
      year: "numeric",
      month: "long",
      day: "numeric",
    });
  };

  if (!idGenre || !genreName) {
    return (
      <Container size="xl" py="xl">
        <Title order={2} ta="center" mb="xl">
          Жанр не найден
        </Title>
      </Container>
    );
  }

  if (loading) {
    return (
      <Container size="xl" py="xl">
        <Paper shadow="sm" p="md" radius="md" mb="xl">
          <Title order={2} ta="center">
            Фильмы жанра: <Text span c={theme.primaryColor}>{getHumanReadableGenre(genreName)}</Text>
          </Title>
        </Paper>
        <Center>
          <Loader size="xl" variant="dots" />
        </Center>
      </Container>
    );
  }

  return (
    <Container size="xl" py="md">
      <Paper shadow="sm" p="md" radius="md" mb="md">
        <Group position="apart">
          <Group spacing="xs">
            <IconMovie size={24} stroke={1.5} color={theme.primaryColor} />
            <Title order={2} size="h3">
              Фильмы жанра:{" "}
              <Text span c={theme.primaryColor}>
                {getHumanReadableGenre(genreName)}
              </Text>
            </Title>
          </Group>
          <Badge size="md" variant="filled" color={theme.primaryColor}>
            {dataFilms.length} фильмов
          </Badge>
        </Group>
      </Paper>

      <Stack spacing="xs">
        {dataFilms.map((film) => (
          <Card
            key={film.id}
            shadow="sm"
            padding={0}
            radius="md"
            withBorder
            style={{ 
              cursor: "pointer",
              transition: "transform 0.2s ease, box-shadow 0.2s ease",
              "&:hover": {
                transform: "translateY(-3px)",
                boxShadow: theme.shadows.sm,
              },
            }}
            onClick={() => handleClick(film.id)}
          >
            <Group noWrap align="stretch" spacing={0}>
              <Card.Section style={{ width: "140px", flexShrink: 0 }}>
                <AspectRatio ratio={2/3} style={{ height: "100%" }}>
                  <Image
                    src={`data:image/jpeg;base64,${Buffer.from(
                      film.img.data
                    ).toString("base64")}`}
                    fit="cover"
                    withPlaceholder
                  />
                </AspectRatio>
              </Card.Section>

              <Stack 
                spacing={8}
                style={{ flex: 1 }} 
                p="md"
              >
                <Title order={3} size="h4" mb={4}>
                  {film.name}
                </Title>

                <Group spacing="xs" mb={8}>
                  <Badge 
                    leftSection={
                      <IconClock size="0.8rem" style={{ marginRight: 3 }} />
                    }
                    size="lg"
                    variant={"light"}
                  >
                    {formatDuration(film.duration)}
                  </Badge>
                  
                  <Badge
                    leftSection={
                      <IconCalendar size="0.8rem" style={{ marginRight: 3 }} />
                    }
                    size="lg"
                    variant={"light"}
                    color={"blue"}
                  >
                    {film.year}
                  </Badge>
                </Group>

                <Divider />

                <Text
                  size="sm"
                  style={{
                    lineHeight: 1.4,
                    maxHeight: "4.2em",
                    overflow: "hidden",
                    textOverflow: "ellipsis",
                    display: "-webkit-box",
                    WebkitLineClamp: 3,
                    WebkitBoxOrient: "vertical",
                  }}
                >
                  {film.description}
                </Text>
              </Stack>
            </Group>
          </Card>
        ))}

        {!loading && dataFilms?.length === 0 && (
          <Paper 
            p="md" 
            radius="md" 
            ta="center"
            bg={theme.colors.gray[0]}
          >
            <Stack align="center" spacing="xs">
              <IconMovie size={32} stroke={1.5} color={theme.colors.gray[5]} />
              <Text size="sm" c="dimmed">
                Фильмы не найдены
              </Text>
            </Stack>
          </Paper>
        )}
      </Stack>
    </Container>
  );
};

export default GenreFilm;
