using System;
using System.Collections.Generic;

// 52장 덱. 섞고 나눠주는 일만 한다.
namespace G26W07WFCardDealer.Model {

    public class Deck {
        private readonly List<Card> cards = new List<Card>();
        private readonly Random random;

        public Deck(Random? random = null) {
            this.random = random ?? new Random();
            Reset();
        }

        // 남은 장수
        public int Count => cards.Count;

        // 52장으로 되돌린다 (4무늬 x 13숫자)
        public void Reset() {
            cards.Clear();
            foreach (Suit suit in Enum.GetValues<Suit>()) {
                foreach (Rank rank in Enum.GetValues<Rank>()) {
                    cards.Add(new Card(suit, rank));
                }
            }
        }

        // Fisher-Yates 셔플: 뒤에서부터 앞쪽 임의 위치와 교환
        public void Shuffle() {
            for (int i = cards.Count - 1; i > 0; i--) {
                int j = random.Next(i + 1);
                (cards[i], cards[j]) = (cards[j], cards[i]);
            }
        }

        // 맨 위에서 count장을 떼어 준다. 덱에서 빠지므로 중복이 생길 수 없다.
        public List<Card> Deal(int count) {
            if (count < 0 || count > cards.Count) {
                throw new ArgumentOutOfRangeException(nameof(count),
                    $"남은 카드는 {cards.Count}장입니다.");
            }

            List<Card> hand = cards.GetRange(cards.Count - count, count);
            cards.RemoveRange(cards.Count - count, count);
            return hand;
        }
    }
}
