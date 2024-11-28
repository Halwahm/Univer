FROM node:16

WORKDIR /server

COPY prisma ./prisma
COPY package*.json ./

RUN npm install

RUN npx prisma generate

COPY . .

EXPOSE 3001

CMD ["node", "app.js"]
