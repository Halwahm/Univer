import { Injectable, NestMiddleware } from '@nestjs/common';
import { Request, Response, NextFunction } from 'express';
import { logger } from '../logger/logger.config';

@Injectable()
export class RequestLoggingMiddleware implements NestMiddleware {
  use(req: Request, res: Response, next: NextFunction) {
    const start = new Date().getTime();
    const { method, originalUrl, headers } = req;
    const { statusCode } = res;
    const userAgent = headers['user-agent'];
    const contentLength = headers['content-length'] || 0;

    res.on('finish', () => {
      const responseTime = new Date().getTime() - start;
      const { rawHeaders } = req;
      const headers = {};
      for (let i = 0; i < rawHeaders.length; i += 2) {
        headers[rawHeaders[i]] = rawHeaders[i + 1];
      }
      const { cookies, body } = req;
      logger.info({
        message: `${method} ${originalUrl} HTTP/${req.httpVersion}`,
        statusCode,
        responseTime: `${responseTime}ms`,
        contentLength,
        headers,
        cookies,
        body,
        userAgent,
      });
    });

    next();
  }
}
