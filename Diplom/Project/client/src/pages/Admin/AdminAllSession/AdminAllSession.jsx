/* eslint-disable jsx-a11y/heading-has-content */
/* eslint-disable jsx-a11y/anchor-is-valid */
import React, {useEffect, useState} from "react";
import {useNavigate} from "react-router-dom";
import {
  ActionIcon,
  Badge,
  Button,
  Card,
  Center,
  Container,
  Group,
  Loader,
  Modal,
  Paper,
  SimpleGrid,
  Stack,
  Text,
  TextInput,
  Title,
  useMantineTheme,
} from "@mantine/core";
import {IconArmchair, IconCalendarTime, IconClock, IconMovie, IconPlus} from "@tabler/icons-react";
import Store from "../../../store/store";
import {notifications} from "@mantine/notifications";
import {ToastContainer} from "react-toastify";

const AdminAllSession = () => {
  const store = new Store();
  const theme = useMantineTheme();
  const [loading, setLoading] = useState(true);
  const [sessions, setSessions] = useState([]);
  const [selectedSession, setSelectedSession] = useState(null);
  const [isEditModalOpen, setIsEditModalOpen] = useState(false);
  const [isDeleteModalOpen, setIsDeleteModalOpen] = useState(false);
  const [formData, setFormData] = useState({
    dateSession: "",
    timeSession: "",
    hallId: "",
    filmId: "",
  });
  const navigate = useNavigate();

  useEffect(() => {
    fetchSessions();
  }, []);

  const fetchSessions = async () => {
    try {
      const response = await store.GetSession();
      setSessions(response.data);
    } catch (error) {
      notifications.show({
        title: 'Ошибка',
        message: 'Не удалось загрузить сеансы',
        color: 'red',
      });
    } finally {
      setLoading(false);
    }
  };

  const handleDelete = (session) => {
    setSelectedSession(session);
    setIsDeleteModalOpen(true);
  };

  const handleSubmit = async (e) => {
    e.preventDefault();
    setLoading(true);

    try {
      await store.UpdateSession(selectedSession.id, formData);
      notifications.show({
        title: 'Успех',
        message: 'Сеанс успешно обновлен',
        color: 'green',
      });
      setIsEditModalOpen(false);
      fetchSessions();
    } catch (error) {
      notifications.show({
        title: 'Ошибка',
        message: 'Не удалось обновить сеанс',
        color: 'red',
      });
    } finally {
      setLoading(false);
    }
  };

  const handleDeleteConfirm = async () => {
    setLoading(true);

    try {
      await store.DeleteSession(selectedSession.id);
      notifications.show({
        title: 'Успех',
        message: 'Сеанс успешно удален',
        color: 'green',
      });
      setIsDeleteModalOpen(false);
      fetchSessions();
    } catch (error) {
      notifications.show({
        title: 'Ошибка',
        message: 'Не удалось удалить сеанс',
        color: 'red',
      });
    } finally {
      setLoading(false);
    }
  };

  if (loading) {
    return (
      <Container size="xl" py="xl">
        <Center>
          <Loader size="xl" variant="dots" />
        </Center>
      </Container>
    );
  }

  return (
    <>
      <ToastContainer />
      <Container size="xl" py="xl">
        <Paper shadow="sm" p="md" radius="md" mb="xl">
          <Group position="apart">
            <Title order={2}>Управление сеансами</Title>
            <Group>
              <Button
                leftIcon={<IconPlus size="1.2rem" />}
                onClick={() => navigate("/AdminAddSession")}
              >
                Добавить сеанс
              </Button>
            </Group>
          </Group>
        </Paper>

        <SimpleGrid
          cols={3}
          spacing="lg"
          breakpoints={[
            { maxWidth: 'md', cols: 2, spacing: 'md' },
            { maxWidth: 'sm', cols: 1, spacing: 'sm' },
          ]}
        >
          {sessions.map((session) => (
            <Card key={session.id} shadow="sm" padding="lg" radius="md" withBorder>
              <Stack spacing="md">
                <Group position="apart">
                  <Group spacing="xs">
                    <IconMovie size="1.2rem" color={theme.colors.blue[6]} />
                    <Text fw={500} size="lg" lineClamp={1}>
                      {session.film?.name || 'Фильм не указан'}
                    </Text>
                  </Group>
                  <Badge 
                    variant="light"
                    color={new Date(session.dateSession) > new Date() ? 'green' : 'red'}
                  >
                    {new Date(session.dateSession) > new Date() ? 'Предстоит' : 'Завершен'}
                  </Badge>
                </Group>

                <Stack spacing="xs">
                  <Group spacing="xs">
                    <IconCalendarTime size="1rem" color={theme.colors.gray[6]} />
                    <Text size="sm">
                      {new Date(session.dateSession).toLocaleDateString()}, {session.timeSession}
                    </Text>
                  </Group>

                  <Group spacing="xs">
                    <IconClock size="1rem" color={theme.colors.gray[6]} />
                    <Text size="sm">
                      Длительность: {session.film?.duration || 'Не указана'}
                    </Text>
                  </Group>

                  <Group spacing="xs">
                    <IconArmchair size="1rem" color={theme.colors.gray[6]} />
                    <Text size="sm">
                      Зал: {session.hall?.name || 'Не указан'}
                    </Text>
                  </Group>
                </Stack>

                <Group position="right" spacing="xs" w={"100%"}>
                  <ActionIcon
                    color="red"
                    variant="light"
                    onClick={() => handleDelete(session)}
                    title={"Удалить сеанс"}
                    w={"100%"}
                    h={"40px"}
                  >
                    {/*<IconTrash size="1.2rem" />*/}
                    Удалить сеанс
                  </ActionIcon>
                </Group>
              </Stack>
            </Card>
          ))}
        </SimpleGrid>

        {!loading && sessions.length === 0 && (
          <Paper p="xl" radius="md" ta="center">
            <Text size="lg" c="dimmed">
              Сеансы не найдены
            </Text>
          </Paper>
        )}
      </Container>

      <Modal
        opened={isEditModalOpen}
        onClose={() => setIsEditModalOpen(false)}
        title={selectedSession ? "Редактировать сеанс" : "Добавить сеанс"}
        size="md"
      >
        <form onSubmit={handleSubmit}>
          <Stack spacing="md">
            <TextInput
              label="Дата"
              type="date"
              value={formData.dateSession}
              onChange={(e) =>
                setFormData({ ...formData, dateSession: e.target.value })
              }
              required
            />
            <TextInput
              label="Время"
              type="time"
              value={formData.timeSession}
              onChange={(e) =>
                setFormData({ ...formData, timeSession: e.target.value })
              }
              required
            />
            <TextInput
              label="ID зала"
              value={formData.hallId}
              onChange={(e) =>
                setFormData({ ...formData, hallId: e.target.value })
              }
              required
            />
            <TextInput
              label="ID фильма"
              value={formData.filmId}
              onChange={(e) =>
                setFormData({ ...formData, filmId: e.target.value })
              }
              required
            />
            <Group position="right" spacing="xs">
              <Button
                variant="default"
                onClick={() => setIsEditModalOpen(false)}
              >
                Отмена
              </Button>
              <Button type="submit" loading={loading}>
                {selectedSession ? "Сохранить" : "Добавить"}
              </Button>
            </Group>
          </Stack>
        </form>
      </Modal>

      <Modal
        opened={isDeleteModalOpen}
        onClose={() => setIsDeleteModalOpen(false)}
        title="Подтверждение удаления"
        size="sm"
      >
        <Stack spacing="md">
          <Text>Вы уверены, что хотите удалить этот сеанс?</Text>
          <Group position="right" spacing="xs">
            <Button
              variant="default"
              onClick={() => setIsDeleteModalOpen(false)}
            >
              Отмена
            </Button>
            <Button
              color="red"
              onClick={handleDeleteConfirm}
              loading={loading}
            >
              Удалить
            </Button>
          </Group>
        </Stack>
      </Modal>
    </>
  );
};

export default AdminAllSession;
