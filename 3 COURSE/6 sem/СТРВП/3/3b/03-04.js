const { v4: uuidv4 } = require('uuid');

// Функция для проверки номера карты
function validateCard(cardNumber) {
    console.log('Card number:', cardNumber);
    if (/^\d+$/.test(cardNumber)) {
        return true;
    } else {
        return false;
    }
}

function createOrder(cardNumber) {
    return new Promise((resolve, reject) => {
        if (!validateCard(cardNumber)) {
            reject(new Error('Card is not valid'));
        } else {
            setTimeout(() => {
                const orderId = uuidv4();
                resolve(orderId);
            }, 5000);
        }
    });
}

function proceedToPayment(orderId) {
    console.log('Order ID:', orderId);
    return new Promise((resolve, reject) => {
        setTimeout(() => {
            if (Math.random() < 0.5) {
                resolve('Payment successful');
            } else {
                reject(new Error('Payment failed'));
            }
        }, 3000);
    });
}

const cardNumber = '123456780123456'; 
createOrder(cardNumber)
    .then(orderId => {
        console.log('Order created successfully. Order ID:', orderId);
        return proceedToPayment(orderId);
    })
    .then(paymentResult => {
        console.log(paymentResult);
    })
    .catch(error => {
        console.error('Error:', error.message);
    });

async function processOrder() {
    try {
        const orderId = await createOrder(cardNumber);
        console.log('Order created successfully. Order ID:', orderId);
        const paymentResult = await proceedToPayment(orderId);
        console.log(paymentResult);
    } catch (error) {
        console.error('Error:', error.message);
    }
}

processOrder();
