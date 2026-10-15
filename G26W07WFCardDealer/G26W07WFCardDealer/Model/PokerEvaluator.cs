using System;
using System.Collections.Generic;
using System.Linq;

// 포커 족보 판별. WinForms를 전혀 참조하지 않는 순수 로직이다.
// 카드 5장만 주면 누가 쓰든 같은 답을 준다 (콘솔, 웹, 테스트 모두 재사용 가능).
namespace G26W07WFCardDealer.Model {

    // 아래로 갈수록 높은 족보. 숫자가 클수록 강하므로 비교 연산자로 우열을 가릴 수 있다.
    public enum HandRank {
        HighCard, OnePair, TwoPair, ThreeOfAKind, Straight,
        Flush, FullHouse, FourOfAKind, StraightFlush, RoyalFlush
    }

    public static class PokerEvaluator {

        public static HandRank Evaluate(IReadOnlyList<Card> hand) {
            if (hand is null) throw new ArgumentNullException(nameof(hand));
            if (hand.Count != 5) throw new ArgumentException("5장이어야 합니다.", nameof(hand));

            // 1) 무늬가 전부 같은가 (플러시)
            bool flush = hand.Select(c => c.Suit).Distinct().Count() == 1;

            // 2) 숫자가 연속인가 (스트레이트)
            int[] values = hand.Select(c => c.HighValue).OrderBy(v => v).ToArray();
            bool straight = IsStraight(values, out int highest);

            // 3) 같은 숫자끼리 묶어 개수만 큰 순으로 정렬
            //    포카드=[4,1]  풀하우스=[3,2]  트리플=[3,1,1]  투페어=[2,2,1]  원페어=[2,1,1,1]
            int[] groups = hand.GroupBy(c => c.Rank)
                               .Select(g => g.Count())
                               .OrderByDescending(n => n)
                               .ToArray();

            // 높은 족보부터 검사해야 한다. (풀하우스를 트리플로 잘못 판정하지 않도록)
            if (straight && flush) return highest == 14 ? HandRank.RoyalFlush : HandRank.StraightFlush;
            if (groups[0] == 4) return HandRank.FourOfAKind;
            if (groups[0] == 3 && groups[1] == 2) return HandRank.FullHouse;
            if (flush) return HandRank.Flush;
            if (straight) return HandRank.Straight;
            if (groups[0] == 3) return HandRank.ThreeOfAKind;
            if (groups[0] == 2 && groups[1] == 2) return HandRank.TwoPair;
            if (groups[0] == 2) return HandRank.OnePair;
            return HandRank.HighCard;
        }

        // 연속된 5장인가? highest에 가장 높은 숫자를 돌려준다.
        private static bool IsStraight(int[] sorted, out int highest) {
            highest = sorted[^1];

            if (sorted.Distinct().Count() != 5) return false;   // 같은 숫자가 있으면 연속 불가
            if (IsRun(sorted)) return true;

            // A-2-3-4-5 는 Ace를 1로 쳐야 스트레이트가 된다 (백스트레이트)
            if (sorted[^1] == 14) {
                int[] low = sorted.Select(v => v == 14 ? 1 : v).OrderBy(v => v).ToArray();
                if (IsRun(low)) {
                    highest = low[^1];
                    return true;
                }
            }
            return false;
        }

        private static bool IsRun(int[] sorted) {
            for (int i = 1; i < sorted.Length; i++) {
                if (sorted[i] != sorted[i - 1] + 1) return false;
            }
            return true;
        }

        // 화면에 보여줄 이름. 포커 용어라서 모델에 둬도 WinForms와는 무관하다.
        public static string ToKorean(this HandRank rank) => rank switch {
            HandRank.RoyalFlush => "로열 플러시",
            HandRank.StraightFlush => "스트레이트 플러시",
            HandRank.FourOfAKind => "포카드",
            HandRank.FullHouse => "풀하우스",
            HandRank.Flush => "플러시",
            HandRank.Straight => "스트레이트",
            HandRank.ThreeOfAKind => "트리플",
            HandRank.TwoPair => "투페어",
            HandRank.OnePair => "원페어",
            _ => "하이카드",
        };
    }
}
