import React, {useEffect, useState} from "react";
import {
  ActionIcon,
  Badge,
  Button,
  Center,
  Container,
  Grid,
  Group,
  Loader,
  Paper,
  rem,
  Stack,
  Text,
  TextInput,
  Title,
  Tooltip,
  useMantineTheme
} from "@mantine/core";
import {IconMovie, IconRefresh, IconSearch} from "@tabler/icons-react";
import Store from "../../../store/store";
import TablePag from "../../../components/pagination/TablePag";
import {notifications} from '@mantine/notifications';

const AdminHome = () => {
  const store = new Store();
  const theme = useMantineTheme();
  const [data, setData] = useState([]);
  const [loading, setLoading] = useState(false);
  const [trig, setTrig] = useState(false);
  const [credentials, setCredentials] = useState({
    search: "",
  });

  const handleChange = (e) => {
    setCredentials((prev) => ({ ...prev, [e.target.id]: e.target.value }));
  };

  const fetchData = async () => {
    setLoading(true);
    try {
      const res = await store.GetFilm();
      setData(res.data);
    } catch (error) {
      notifications.show({
        title: 'Ошибка',
        message: 'Не удалось загрузить фильмы',
        color: 'red',
      });
    } finally {
      setLoading(false);
    }
  };

  useEffect(() => {
    fetchData();
  }, []);

  const handleSearch = async (e) => {
    e.preventDefault();
    setLoading(true);
    try {
      const res = await store.GetFilmByName(credentials);
      setData(res.data);
      setTrig(true);
    } catch (error) {
      notifications.show({
        title: 'Ошибка',
        message: 'Не удалось найти фильмы',
        color: 'red',
      });
    } finally {
      setLoading(false);
    }
  };

  return (
    <Container size="lg" py="xl">
      <Stack spacing="xl">
        <Group position="apart" align="center">
          <Title order={1} align="center" style={{
            fontSize: rem(32),
            fontWeight: 900,
            letterSpacing: -1,
          }}>
            Hm
          </Title>
          <Tooltip label="Обновить список">
            <ActionIcon
              variant="light"
              size="lg"
              onClick={fetchData}
              loading={loading}
            >
              <IconRefresh size="1.2rem" />
            </ActionIcon>
          </Tooltip>
        </Group>

        <Paper shadow="sm" py="lg" radius="md">
          <Stack spacing="md">
            <Group position="apart">
              <Title order={3}>Найди свой фильм</Title>
              <Badge size="lg" variant="light">
                {data.length} фильмов
              </Badge>
            </Group>

            <form onSubmit={handleSearch}>
              <Grid>
                <Grid.Col span={10}>
                  <TextInput
                    id="search"
                    placeholder="Введите название фильма..."
                    value={credentials.search}
                    onChange={handleChange}
                    size="md"
                    icon={<IconSearch size="1rem" />}
                  />
                </Grid.Col>
                <Grid.Col span={2}>
                  <Button
                    type="submit"
                    fullWidth
                    size="md"
                    loading={loading}
                  >
                    Найти
                  </Button>
                </Grid.Col>
              </Grid>
            </form>
          </Stack>
        </Paper>

        {(data?.length >= 1 || trig) && (
          <Paper shadow="sm" py="lg" radius="md">
            {loading ? (
              <Center py="xl">
                <Loader size="xl" variant="dots" />
              </Center>
            ) : (
              <TablePag data={data} />
            )}
          </Paper>
        )}

        {!loading && (!data?.length && !trig) && (
          <Center py="xl">
            <Stack align="center" spacing="md">
              <IconMovie size={48} color={theme.colors.gray[4]} />
              <Text color="dimmed" size="lg">
                Нет доступных фильмов
              </Text>
            </Stack>
          </Center>
        )}
      </Stack>
    </Container>
  );
};

export default AdminHome;