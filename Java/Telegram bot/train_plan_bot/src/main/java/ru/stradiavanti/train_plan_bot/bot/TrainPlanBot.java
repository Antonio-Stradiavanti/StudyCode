// Определяет пространство имен для всех классов, объявленных в этом исходном файле
package ru.stradiavanti.train_plan_bot.bot;

import org.telegram.telegrambots.bots.TelegramLongPollingBot;
import org.telegram.telegrambots.meta.api.objects.Update;

public class TrainPlanBot extends TelegramLongPollingBot {
    public TrainPlanBot(String botToken) {
        super(botToken);
    }

    @Override
    // Реализуем абстрактный метод
    public void onUpdateReceived(Update update) {
    }

    @Override
    public String getBotUsername() {
        return null;
    }
}
