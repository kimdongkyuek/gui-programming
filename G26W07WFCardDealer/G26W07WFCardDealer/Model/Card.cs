// 카드 한 장. 화면(View)과 무관한 순수 데이터.
namespace G26W07WFCardDealer.Model {

    // 무늬 4종
    public enum Suit { Spades, Hearts, Diamonds, Clubs }

    // 숫자 13종. Ace를 1로 두어 (int)Rank 가 그대로 숫자가 되게 함
    public enum Rank {
        Ace = 1, Two, Three, Four, Five, Six, Seven, Eight, Nine, Ten, Jack, Queen, King
    }

    public readonly struct Card {
        public Suit Suit { get; }
        public Rank Rank { get; }

        public Card(Suit suit, Rank rank) {
            Suit = suit;
            Rank = rank;
        }

        // J, Q, K 인가? (그림 카드)
        public bool IsFace => Rank is Rank.Jack or Rank.Queen or Rank.King;

        // 포커에서 Ace는 가장 높은 카드(14)로 취급한다
        public int HighValue => Rank == Rank.Ace ? 14 : (int)Rank;

        public override string ToString() => $"{Rank} of {Suit}";
    }
}
