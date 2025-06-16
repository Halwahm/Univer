FROM node:18.19.0

# Create app directory
WORKDIR /usr/src/app

# Install build dependencies
RUN apt-get update && apt-get install -y build-essential

# Install app dependencies
COPY package*.json ./
RUN npm install

# Bundle app source
COPY . .

RUN npm run build

# Uninstall and reinstall bcrypt
RUN npm uninstall bcrypt
RUN npm install bcrypt

EXPOSE 5000

CMD [ "node", "dist/main" ]
