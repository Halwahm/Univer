import React, {useEffect, useState} from "react";
import {
  ActionIcon,
  Badge,
  Button,
  Card,
  Container,
  Grid,
  Group,
  LoadingOverlay,
  Modal,
  NumberInput,
  Stack,
  Text,
  TextInput,
  Title,
  useMantineTheme
} from "@mantine/core";
import {IconBuilding, IconCurrencyDollar, IconPlus, IconSalt, IconTrash} from "@tabler/icons-react";
import Store from "../../../store/store";
import {useNavigate} from "react-router-dom";
import {notifications} from "@mantine/notifications";

const AdminAllHall = () => {
  const store = new Store();
  const navigate = useNavigate();
  const theme = useMantineTheme();
  const [loading, setLoading] = useState(true);
  const [halls, setHalls] = useState([]);
  const [deleteModalOpen, setDeleteModalOpen] = useState(false);
  const [selectedHall, setSelectedHall] = useState(null);
  const [editModalOpen, setEditModalOpen] = useState(false);
  const [editFormData, setEditFormData] = useState({
    name: "",
    coast_vip: "",
    coast_norm: "",
    count_place: "",
    count_rows: "",
  });

  const fetchHalls = async () => {
    try {
      const response = await store.GetAllHall();
      setHalls(response.data);
    } catch (error) {
      notifications.show({
        title: 'Ошибка',
        message: 'Не удалось загрузить список залов',
        color: 'red',
      });
    } finally {
      setLoading(false);
    }
  };

  useEffect(() => {
    fetchHalls();
  }, []);

  const handleDelete = async () => {
    try {
      await store.DeleteHall(selectedHall.id);
      notifications.show({
        title: 'Успех',
        message: 'Зал успешно удален',
        color: 'green',
      });
      fetchHalls();
      setDeleteModalOpen(false);
    } catch (error) {
      notifications.show({
        title: 'Ошибка',
        message: 'Не удалось удалить зал',
        color: 'red',
      });
    }
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
        <Group position="apart">
          <Title order={2}>Список залов</Title>
          <Button
            leftIcon={<IconPlus size="1rem" />}
            onClick={() => navigate('/AdminAddHall')}
          >
            Добавить зал
          </Button>
        </Group>

        <Grid>
          {halls.map((hall) => (
            <Grid.Col key={hall.id} span={4}>
              <Card shadow="sm" padding="lg" radius="md" withBorder>
                <Card.Section p="md">
                  <Group position="apart" mb="xs">
                    <Text weight={500} size="lg">
                      {hall.name}
                    </Text>
                    <Group spacing="xs">
                      <ActionIcon
                        color="red"
                        variant="light"
                        onClick={() => {
                          setSelectedHall(hall);
                          setDeleteModalOpen(true);
                        }}
                      >
                        <IconTrash size="1rem" />
                      </ActionIcon>
                    </Group>
                  </Group>

                  <Group spacing="xs" mb="md">
                    <Badge color="blue" variant="light">
                      {hall.count_rows} рядов
                    </Badge>
                    <Badge color="green" variant="light">
                      {hall.count_place} мест в ряду
                    </Badge>
                  </Group>

                  <Stack spacing="xs">
                    <Group>
                      <IconCurrencyDollar size="1rem" />
                      <Text size="sm">Обычные места: {hall.coast_norm} ₽</Text>
                    </Group>
                    <Group>
                      <IconSalt size="1rem" />
                      <Text size="sm">VIP места: {hall.coast_vip} ₽</Text>
                    </Group>
                  </Stack>
                </Card.Section>
              </Card>
            </Grid.Col>
          ))}
        </Grid>

        {/* Модальное окно удаления */}
        <Modal
          opened={deleteModalOpen}
          onClose={() => setDeleteModalOpen(false)}
          title="Подтверждение удаления"
        >
          <Stack spacing="md">
            <Text>Вы уверены, что хотите удалить зал "{selectedHall?.name}"?</Text>
            <Group position="right">
              <Button variant="default" onClick={() => setDeleteModalOpen(false)}>
                Отмена
              </Button>
              <Button color="red" onClick={handleDelete}>
                Удалить
              </Button>
            </Group>
          </Stack>
        </Modal>

        {/* Модальное окно редактирования */}
        <Modal
          opened={editModalOpen}
          onClose={() => setEditModalOpen(false)}
          title="Редактирование зала"
          size="lg"
        >
          <Stack spacing="md">
            <TextInput
              label="Название зала"
              value={editFormData.name}
              onChange={(e) => setEditFormData(prev => ({ ...prev, name: e.target.value }))}
              icon={<IconBuilding size="1rem" />}
              required
            />

            <Grid>
              <Grid.Col span={6}>
                <NumberInput
                  label="Количество рядов"
                  value={editFormData.count_rows}
                  onChange={(value) => setEditFormData(prev => ({ ...prev, count_rows: value }))}
                  min={1}
                  max={20}
                  required
                />
              </Grid.Col>

              <Grid.Col span={6}>
                <NumberInput
                  label="Количество мест в ряду"
                  value={editFormData.count_place}
                  onChange={(value) => setEditFormData(prev => ({ ...prev, count_place: value }))}
                  min={1}
                  max={30}
                  required
                />
              </Grid.Col>
            </Grid>

            <Grid>
              <Grid.Col span={6}>
                <NumberInput
                  label="Стоимость обычных билетов"
                  value={editFormData.coast_norm}
                  onChange={(value) => setEditFormData(prev => ({ ...prev, coast_norm: value }))}
                  min={0}
                  icon={<IconCurrencyDollar size="1rem" />}
                  required
                />
              </Grid.Col>

              <Grid.Col span={6}>
                <NumberInput
                  label="Стоимость VIP билетов"
                  value={editFormData.coast_vip}
                  onChange={(value) => setEditFormData(prev => ({ ...prev, coast_vip: value }))}
                  min={0}
                  icon={<IconSalt size="1rem" />}
                  required
                />
              </Grid.Col>
            </Grid>
          </Stack>
        </Modal>
      </Stack>
    </Container>
  );
};

export default AdminAllHall; 