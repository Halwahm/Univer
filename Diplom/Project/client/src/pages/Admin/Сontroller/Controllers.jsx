/* eslint-disable jsx-a11y/alt-text */
/* eslint-disable jsx-a11y/anchor-is-valid */
import "../../../lib/boxicons/css/boxicons.min.css";
import "../../../lib/datatables/datatables.min.css";
import "../../../css/cinemaDataTable.css";
import Store from "../../../store/store";
import {useEffect, useState} from "react";
import {Html5Qrcode} from "html5-qrcode";
import {
  Badge,
  Card,
  Center,
  Container,
  Group,
  Paper,
  Stack,
  Switch,
  Text,
  ThemeIcon,
  Title,
  Transition,
} from "@mantine/core";
import {notifications} from "@mantine/notifications";
import {IconCheck, IconQrcode, IconScan, IconTicket, IconX} from "@tabler/icons-react";

const TheController = () => {
  const store = new Store();
  const [isEnable, setEnabled] = useState(false);
  const [qrMessage, setQRMessage] = useState("");
  const [lastScanResult, setLastScanResult] = useState(null);
  const [lastNotificationId, setLastNotificationId] = useState(null);

  useEffect(() => {
    const config = { 
      fps: 10, 
      qrbox: { width: 300, height: 300 },
      aspectRatio: 1.0
    };

    const htm15QrCode = new Html5Qrcode("qrCodeContainer");

    const qrScanerStop = () => {
      if (htm15QrCode && htm15QrCode.isScanning) {
        htm15QrCode
          .stop()
          .then(() => console.log("Scanner stopped"))
          .catch((err) => console.error("Error stopping scanner:", err));
      }
    };

    const showNotification = (isValid, data) => {
      // Очищаем предыдущее уведомление, если оно есть
      if (lastNotificationId) {
        notifications.hide(lastNotificationId);
      }

      // Показываем новое уведомление
      const id = notifications.show({
        id: `scan-${Date.now()}`, // Уникальный ID для уведомления
        title: isValid ? 'Билет действителен' : 'Билет недействителен',
        message: isValid 
          ? `Место: ${data.place.place}`
          : 'QR-код не найден в системе',
        color: isValid ? 'green' : 'red',
        icon: isValid ? <IconCheck size="1.1rem" /> : <IconX size="1.1rem" />,
        autoClose: 5000, // Автоматически закрывать через 3 секунды
      });

      setLastNotificationId(id);
    };

    const qrCodeSuccess = async (decodedText) => {
      setQRMessage(decodedText);
      try {
        const res = await store.CheckTicketCon(decodedText);
        const isValid = res.data.length > 0;
        
        setLastScanResult({
          isValid,
          message: isValid 
            ? `Билет действителен. Место: ${res.data[0].place.place}`
            : "Билет недействителен",
          timestamp: new Date(),
          place: isValid ? res.data[0].place.place : null
        });

        showNotification(isValid, res.data[0]);

      } catch (error) {
        console.error('Error checking ticket:', error);
        // Очищаем предыдущее уведомление перед показом ошибки
        if (lastNotificationId) {
          notifications.hide(lastNotificationId);
        }
        const id = notifications.show({
          title: 'Ошибка',
          message: 'Не удалось проверить билет',
          color: 'red',
          autoClose: 3000,
        });
        setLastNotificationId(id);
      }
    };

    if (isEnable) {
      htm15QrCode.start(
        { facingMode: "environment" },
        config,
        qrCodeSuccess,
        (errorMessage) => {
          console.log(errorMessage);
        }
      );
      setQRMessage("");
    } else {
      qrScanerStop();
    }

    return () => {
      qrScanerStop();
      if (lastNotificationId) {
        notifications.hide(lastNotificationId);
      }
    };
  }, [isEnable, lastNotificationId]);

  return (
    <Container size="md" py="xl">
      <Stack spacing="xl">
        <Card shadow="sm" p="lg" radius="md" withBorder>
          <Stack spacing="md">
            <Group position="apart">
              <Group spacing="xs">
                <ThemeIcon size="xl" radius="md" variant="light">
                  <IconQrcode size="1.5rem" />
                </ThemeIcon>
                <Title order={2}>Сканер билетов</Title>
              </Group>
              <Switch
                size="lg"
                onLabel="ON"
                offLabel="OFF"
                checked={isEnable}
                onChange={() => setEnabled(!isEnable)}
                color="green"
              />
            </Group>
            
            <Text c="dimmed" size="sm">
              Наведите камеру на QR-код билета для сканирования
            </Text>
          </Stack>
        </Card>

        <Paper shadow="sm" p="lg" radius="md" withBorder>
          <Stack spacing="md" align="center">
            <Card
              id="qrCodeContainer" 
              style={{
                width: '100%',
                maxWidth: '600px',
                height: '600px',
                borderRadius: '8px',
                overflow: 'hidden',
              }}
            >
            
            {!isEnable && (
              <Center 
                style={{ 
                  position: 'absolute',
                  top: '50%',
                  left: '50%',
                  transform: 'translate(-50%, -50%)',
                  pointerEvents: 'none'
                }}
              >
                <ThemeIcon size={80} radius={40} variant="light">
                  <IconScan size="3rem" />
                </ThemeIcon>
              </Center>
            )}
            </Card>
          </Stack>
        </Paper>

        {lastScanResult && (
          <Transition mounted={true} transition="slide-up" duration={400} timingFunction="ease">
            {(styles) => (
              <Card shadow="sm" p="lg" radius="md" withBorder style={styles}>
                <Group position="apart">
                  <Group spacing="xs">
                    <ThemeIcon 
                      size="lg" 
                      radius="md" 
                      color={lastScanResult.isValid ? 'green' : 'red'}
                      variant="light"
                    >
                      {lastScanResult.isValid ? <IconCheck size="1.2rem" /> : <IconX size="1.2rem" />}
                    </ThemeIcon>
                    <Stack spacing={4}>
                      <Text weight={500}>
                        {lastScanResult.message}
                      </Text>
                      <Text size="xs" color="dimmed">
                        {lastScanResult.timestamp.toLocaleTimeString()}
                      </Text>
                    </Stack>
                  </Group>
                  
                  {lastScanResult.isValid && (
                    <Badge 
                      size="lg"
                      variant={"light"}
                      leftSection={<IconTicket size="0.9rem" />}
                    >
                      Место {lastScanResult.place}
                    </Badge>
                  )}
                </Group>
              </Card>
            )}
          </Transition>
        )}
      </Stack>
    </Container>
  );
};

export default TheController;
