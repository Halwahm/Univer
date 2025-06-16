/* eslint-disable jsx-a11y/heading-has-content */
/* eslint-disable jsx-a11y/anchor-is-valid */
import React, {useEffect, useState} from "react";
import {
  ActionIcon,
  Button,
  Container,
  Group,
  LoadingOverlay,
  Modal,
  Paper,
  Stack,
  Table,
  Text,
  TextInput,
  Title,
  useMantineTheme,
} from "@mantine/core";
import {IconTrash} from "@tabler/icons-react";
import Store from "../../../store/store";
import {notifications} from "@mantine/notifications";
import {ToastContainer} from "react-toastify";
import {useNavigate} from "react-router-dom";
import {getHumanReadableGenre} from "../../../utils/genreUtils";

const AdminAllFilm = () => {
  const store = new Store();
  const navigate = useNavigate();
  const theme = useMantineTheme();
  const [loading, setLoading] = useState(true);
  const [films, setFilms] = useState([]);
  const [selectedFilm, setSelectedFilm] = useState(null);
  const [isEditModalOpen, setIsEditModalOpen] = useState(false);
  const [isDeleteModalOpen, setIsDeleteModalOpen] = useState(false);
  const [formData, setFormData] = useState({
    name: "",
    description: "",
    duration: "",
    genreId: "",
  });

  useEffect(() => {
    fetchFilms();
  }, []);

  const fetchFilms = async () => {
    try {
      const response = await store.GetFilm();
      console.log('Response:', response);
      if (response && response.data) {
        setFilms(response.data);
      } else {
        setFilms([]);
      }
    } catch (error) {
      console.error('Error fetching films:', error);
      notifications.show({
        title: 'Ошибка',
        message: 'Не удалось загрузить фильмы',
        color: 'red',
      });
      setFilms([]);
    } finally {
      setLoading(false);
    }
  };

  const handleDelete = (film) => {
    setSelectedFilm(film);
    setIsDeleteModalOpen(true);
  };

  const handleSubmit = async (e) => {
    e.preventDefault();
    setLoading(true);

    try {
      if (selectedFilm) {
        await store.UpdateFilm(selectedFilm.id, formData);
        notifications.show({
          title: 'Успех',
          message: 'Фильм успешно обновлен',
          color: 'green',
        });
      } else {
        await store.CreateFilm(formData);
        notifications.show({
          title: 'Успех',
          message: 'Фильм успешно добавлен',
          color: 'green',
        });
      }
      setIsEditModalOpen(false);
      fetchFilms();
    } catch (error) {
      notifications.show({
        title: 'Ошибка',
        message: 'Не удалось сохранить фильм',
        color: 'red',
      });
    } finally {
      setLoading(false);
    }
  };

  const handleDeleteConfirm = async () => {
    setLoading(true);

    try {
      await store.DeleteFilm(selectedFilm.id);
      notifications.show({
        title: 'Успех',
        message: 'Фильм успешно удален',
        color: 'green',
      });
      setIsDeleteModalOpen(false);
      fetchFilms();
    } catch (error) {
      notifications.show({
        title: 'Ошибка',
        message: 'Не удалось удалить фильм',
        color: 'red',
      });
    } finally {
      setLoading(false);
    }
  };

  if (loading) {
    return (
      <Container size="xl" py="xl">
        <LoadingOverlay visible={true} />
      </Container>
    );
  }

  return (
    <>
      <ToastContainer />
      <Container size="xl" py="xl">
        <Stack spacing="xl">
          <Group>
            <Title order={1} className="h3 mb-3">
              <strong>Все фильмы</strong>
            </Title>
            <Button variant={"light"} onClick={() => navigate("/AdminAddFilm")}>Добавить фильм</Button>
          </Group>

          <Paper p="md" radius="md" withBorder>
            <Table striped highlightOnHover withColumnBorders>
              <Table.Thead>
                <Table.Tr>
                  <Table.Th>Название</Table.Th>
                  <Table.Th>Описание</Table.Th>
                  <Table.Th>Жанр</Table.Th>
                  <Table.Th>Длительность</Table.Th>
                  <Table.Th>Действия</Table.Th>
                </Table.Tr>
              </Table.Thead>
              <Table.Tbody>
                {films.map((film) => (
                  <Table.Tr key={film.id}>
                    <Table.Td>{film.name}</Table.Td>
                    <Table.Td><Text lineClamp={2}>{film.description}</Text></Table.Td>
                    <Table.Td>{getHumanReadableGenre(film.genre?.name)}</Table.Td>
                    <Table.Td>{film.duration} мин</Table.Td>
                    <Table.Td>
                      <Group spacing="xs">
                        <ActionIcon
                          color="red"
                          variant="light"
                          onClick={() => handleDelete(film)}
                        >
                          <IconTrash size="1rem" />
                        </ActionIcon>
                      </Group>
                    </Table.Td>
                  </Table.Tr>
                ))}
              </Table.Tbody>
            </Table>
          </Paper>
        </Stack>
      </Container>

      <Modal
        opened={isEditModalOpen}
        onClose={() => setIsEditModalOpen(false)}
        title={selectedFilm ? "Редактировать фильм" : "Добавить фильм"}
        size="md"
      >
        <form onSubmit={handleSubmit}>
          <Stack spacing="md">
            <TextInput
              label="Название"
              value={formData.name}
              onChange={(e) =>
                setFormData({ ...formData, name: e.target.value })
              }
              required
            />
            <TextInput
              label="Описание"
              value={formData.description}
              onChange={(e) =>
                setFormData({ ...formData, description: e.target.value })
              }
              required
            />
            <TextInput
              label="Длительность (в минутах)"
              type="number"
              value={formData.duration}
              onChange={(e) =>
                setFormData({ ...formData, duration: e.target.value })
              }
              required
            />
            <TextInput
              label="ID жанра"
              value={formData.genreId}
              onChange={(e) =>
                setFormData({ ...formData, genreId: e.target.value })
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
                {selectedFilm ? "Сохранить" : "Добавить"}
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
          <Text>Вы уверены, что хотите удалить этот фильм?</Text>
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

export default AdminAllFilm;
